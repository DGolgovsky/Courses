/* Used FreeBSD */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#include <string.h>
#include <stdio.h>

#include <sys/event.h>

int set_nonblock(int fd)
{
    int flags;
#if defined(O_NONBLOCK)
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctl(fd, FIOBIO, &flags);
#endif
}

int main(int argc, char **argv)
{
    int MasterSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in SockAddr;
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(12345);
    SockAddr.sin_addr.s_addr = 0;

    bind(MasterSocket, (struct sockaddr *)&SockAddr, sizeof(SockAddr));

    set_nonblock(MasterSocket);

    listen(MasterSocket, SOMAXCONN);

    int KQueue = kqueue();

    struct kevent KEvent;
    bzero(&KEvent, sizeof(KEvent));
    EV_SET(&KEvent, MasterSocket, EVFILT_READ, EV_ADD, 0, 0, 0);
    kevent(KQueue, &KEvent, 1, NULL, 0, NULL);

    while (true) {
        bzero(&KEvent, sizeof(KEvent));
        kevent(KQueue, NULL, 0, &Kevent, 1, NULL);

        if (KEvent.filter = EVFILT_READ) {
            if (KEvent.ident == MasterSocket) {
                int SlaveSocket = accept(MasterSocket, 0, 0);
                set_nonblock(SlaveSocket);

                bzero(&KEvent, sizeof(KEvent));
                EV_SET(&KEvent, SlaveSocket, EVFILT_READ, EV_ADD, 0, 0, 0);
                kevent(KQueue, &KEvent, 1, NULL, 0, NULL);
            } else {
                static char Buffer[1024];
                int RecvSize = recv(KEvent.ident, Buffer, 1024, MSG_NOSIGNAL);
                if (RecvSize <= 0) {
                    close(KEvent.ident);
                    printf("disconnected!\n");
                } else {
                    send(KEvent.ident, Buffer, RecvSize, MSG_NOSIGNAL);
                }
            }
        }
    }

    return 0;
}
