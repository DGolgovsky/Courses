/** Task
 * Написать чат-сервер.
 * Каждое сообщение, посланное одним клиентом,
 * передается всем остальным.
 * К началу каждого сообщения присоединяется IP-адрес клиента.
 * Всем клиентам приходят сообщения о подключении
 * новых участников и об отключении существующих.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

#include <cstring>
#include <sstream>
#include <unordered_map>

#define RECV_BUFFER_SIZE 1024
#define LISTENING_PORT 2017
#define MAX_EVENTS 1024

int set_nonblock(int fd)
{
    int flags;
#ifdef O_NONBLOCK
    //printf("O_NONBLOCK defined\n");
    if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    //printf("O_NONBLOCK undefined\n");
    flags = 1;
    return ioctl(fd, FIOBIO, &flags);
#endif
}

void send_message_to(unsigned sender_descriptor,
                     std::unordered_map<unsigned, struct sockaddr_in>& clients,
                     const char* buffer,
                     size_t length)
{
    char ip_address[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clients[sender_descriptor].sin_addr, ip_address, INET_ADDRSTRLEN);
    std::uint16_t port = clients[sender_descriptor].sin_port;

    std::stringstream result_msg;
    result_msg << ip_address << ":" << port << ": " << buffer;

    for (auto &client : clients)
        if (client.first != sender_descriptor)
            send(client.first,
                 result_msg.str().c_str(),
                 result_msg.str().length(),
                 MSG_NOSIGNAL);
}

int main(int argc, char **argv)
{
    int master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(LISTENING_PORT);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(master_socket, (struct sockaddr *)(&sock_addr), sizeof(sockaddr));
    set_nonblock(master_socket);

    listen(master_socket, SOMAXCONN);

    int epoll_descriptor = epoll_create1(0);

    struct epoll_event event;
    event.data.fd = master_socket;
    event.events = EPOLLIN;
    epoll_ctl(epoll_descriptor, EPOLL_CTL_ADD, master_socket, &event);

    std::unordered_map<unsigned, struct sockaddr_in> slave_sockets;

    while (true) {
        struct epoll_event events[MAX_EVENTS];
        int n = epoll_wait(epoll_descriptor, events, MAX_EVENTS, -1);
        for (int i = 0; i < n; ++i) {
            if (events[i].data.fd == master_socket) {
                struct sockaddr_in client_addr;
                socklen_t client_addr_size = sizeof(client_addr);
                int slave_socket = accept(master_socket,
                        (struct sockaddr *)&client_addr,
                        &client_addr_size);

                set_nonblock(slave_socket);

                struct epoll_event tmp_event;
                tmp_event.data.fd = slave_socket;
                tmp_event.events = EPOLLIN;
                epoll_ctl(epoll_descriptor, EPOLL_CTL_ADD, slave_socket, &tmp_event);

                slave_sockets[slave_socket] = client_addr;
                const char connect_msg[] = "[New client connected]\n";
                send_message_to(slave_socket, slave_sockets, connect_msg, strlen(connect_msg));
            } else {
                static char buffer[RECV_BUFFER_SIZE];
                memset(buffer, 0, RECV_BUFFER_SIZE);
                int recv_n = recv(events[i].data.fd, buffer, RECV_BUFFER_SIZE, MSG_NOSIGNAL);
                if (recv_n == 0 && errno != EAGAIN) {
                    shutdown(events[i].data.fd, SHUT_RDWR);
                    close(events[i].data.fd);
                    const char disconnect_msg[] = "[Client disconnected]\n";
                    send_message_to(events[i].data.fd,
                            slave_sockets,
                            disconnect_msg,
                            strlen(disconnect_msg));
                    slave_sockets.erase(events[i].data.fd);
                } else if (recv_n > 0) {
                    send_message_to(events[i].data.fd, slave_sockets, buffer, recv_n);
                }
            }
        }
    }

    return 0;
}

