#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

static const int SOCKET_COMMON_ERROR = -1;

static const int BUFFER_SIZE = 2048;

int main(int argc, char **argv)
{
    int ss = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ss == SOCKET_COMMON_ERROR) {
        std::cerr << "Error on open server socket";
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sai;
    sai.sin_family = AF_INET;
    sai.sin_port = htons(12345);
    sai.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(ss, (struct sockaddr *) (&sai), sizeof(sai)) == SOCKET_COMMON_ERROR) {
        std::cerr << "Error on bind server socket";
        close(ss);
        exit(EXIT_FAILURE);
    }

    if(listen(ss, SOMAXCONN) == SOCKET_COMMON_ERROR) {
        std::cerr << "Error on start listen server socket" << std::endl;
        close(ss);
        exit(EXIT_FAILURE);
    }

    int sc;
    ssize_t ri;
    char buffer[BUFFER_SIZE];
    std::string r;

    std::cout << "Ready for connection..." << std::endl;

    while ((sc = accept(ss, 0, 0)) > 0) {
        if ((ri = recv(sc, buffer, BUFFER_SIZE, 0)) > 0) {
            send(sc, buffer, ri, 0);

            r.append(buffer, ri);
            std::cout << "  > " << r << std::endl;
        }
        close(sc);
    }

    close(ss);

    return 0;
}
