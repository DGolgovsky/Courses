#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    /*
     * connect (int fd, struct sockaddr *, size_t);
     *
     * // Close connection:
     * shutdown(s, SHUT_RDWR <-->
     *             SHUT_RD   ---> read close
     *             SHUT_WR   <--- write close
     *             );
     * close(s);
     */

    int Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12345);
    SockAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    connect(Socket, (struct sockaddr *)(&SockAddr), sizeof(SockAddr));

    char Buffer[] = "PING";
    send(Socket, Buffer, 4, MSG_NOSIGNAL);
    recv(Socket, Buffer, 4, MSG_NOSIGNAL);

    shutdown(Socket, SHUT_RDWR);
    close(Socket);

    printf("%s\n", Buffer);

    return 0;
}

