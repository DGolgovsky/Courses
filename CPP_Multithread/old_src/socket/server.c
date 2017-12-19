#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    /* int s = socket(domain, type, protocol)
     * domain:
     *  AF_INET - IPv4
     *  AF_INET6 - IPv6
     *  AF_UNIX - Unix Socket
     * type:
     *  SOCK_STREAM - TCP
     *  SOCK_DGRAM - UDP
     * protocol:
     *  0 - default
     *  IPPROTO_TCP
     *  IPPROTO_UDP
     *
     * bind (s, (struct sockaddr *)sa, sizeof(sa));
     *  struct sockaddr_in sa; <-- IPv4
     *  struct sockaddr_in6 sa; <-- IPv6
     *      sa.sin_family = AF_INET;
     *      sa.sin_port = htons(12345);
     *      sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
     *          INADDR_LOOPBACK (127.0.0.1) только локальные соединения
     *          INADDR_ANY (0.0.0.0)
     *      ip = inet_addr("10.0.0.1") <-- Convert address string to int
     *           inet_pton(AF_INET, "10.0.0.1", &(sa.sin_addr));
     *
     *  struct sockaddr_un sa; <-- UNIX Socket
     *      sa.sun_family = AF_UNIX;
     *      strcpy(sa.sun_path, "/tmp/a.sock");
     *
     * listen (s, SOMAXCONN); // длина очереди соединений 128 default
     * while (s1 = accept(s, 0, 0)) {} s1 - новый сокет последовательный
     *      1st 0 <-- struct sockaddr * --> пара IP и PORT клиента
     *      2nd 0 <-- size *
     *
     * size_t read (int fd, void *buf, size_t count);
     *        recv (int fd, void *buf, size_t count, int flags);
     * size_t write (int fd, const void *buf, size_t count);
     *        send (int fd, const void *buf, size_t count, int flags);
     *      SIGPIPE <-- Sys error
     *      signal(SIGPIPE, SIG_IGN) - ignoring sygnal
     *  flags:
     *      MSG_NOSIGNAL
     *
     */

    int MasterSocket = socket( // Дескриптор сокета
            AF_INET /* IPv4 */,
            SOCK_STREAM /* TCP */,
            IPPROTO_TCP);

    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12345);
    SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0
    bind(MasterSocket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr));

    listen(MasterSocket, SOMAXCONN);

    while(1) {
        int SlaveSocket = accept(MasterSocket, 0, 0);

        int Buffer[5] = {0, 0, 0, 0, 0};

/*
        unsigned int counter = 0;
        while(counter < 4) {
            int res = recv(SlaveSocket, Buffer + 4 - counter, counter, MSG_NOSIGNAL);
            if(res > 0)
                counter += res;
        }
*/        
        recv(SlaveSocket, Buffer, 4, MSG_NOSIGNAL);
        send(SlaveSocket, Buffer, 4, MSG_NOSIGNAL);
        shutdown(SlaveSocket, SHUT_RDWR);
        close(SlaveSocket);

        printf("%s\n", Buffer);
    }

    return 0;
}

