#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define OPT_MAX_SIZE 30
#define BUF_SIZE 1024

static char usage[] = "usage: %s -h <ip> -p <port> -d <dir>\n";

void parse(int argc, char* const argv[], char *ip, uint16_t *port, char *dir);
int set_nonblock(int sd);
void* handle_request(void *arg);

int main(int argc, char *argv[])
{
    // daemonize me
    signal(SIGHUP, SIG_IGN);
    daemon(1, 1); // do not change dir and do not close stdin, stdout and stderr

    // parsing the command line options (not very accurately but OK)
    char ip[OPT_MAX_SIZE], dir[OPT_MAX_SIZE];
    uint16_t port = 12345;
    parse(argc, argv, ip, &port, dir);
    //printf("ip = \"%s\"\nport = %lu\ndir = \"%s\"\n", ip, port, dir);

    if (!*ip)
        strcpy(ip, "127.0.0.1");
    if (!*dir)
        strcpy(dir, "/tmp");

    // WARNING! NO ERROR CHECKING BELOW!!!

    chdir(dir);

    int server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //set_nonblock(server);

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = inet_addr(ip);
    bind(server, (struct sockaddr *)&saddr, sizeof(saddr));
    listen(server, SOMAXCONN);

    pthread_attr_t t_attr;
    pthread_attr_init(&t_attr);
    pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);
    while (1)
    {
        int client = accept(server, 0, 0);
        pthread_t t;
        pthread_create(&t, &t_attr, handle_request, (void *)&client);
    }
    pthread_attr_destroy(&t_attr);
    return 0;
}

void* handle_request(void *arg)
{
    int client = *(int *)arg;

    // get the request string from client
    unsigned int i = 0;
    char request[BUF_SIZE];
    while (i < BUF_SIZE - 1)
    {
        char c;
        ssize_t sz = recv(client, &c, 1, MSG_NOSIGNAL);
        if (sz > 0)
        {
            if (c == '\r' || c == '\n')
                break;
            request[i++] = c;
        }
        else
            break;
    }
    request[i] = '\0';

    //printf("request: \"%s\"\n", request);

    // get the method name
    i = 0;
    char method[BUF_SIZE];
    while (request[i] && !isspace(request[i]) && i < BUF_SIZE)
    {
        method[i] = request[i];
        ++i;
    }
    method[i] = '\0';

    //printf("method: \"%s\"\n", method);

    // switch between methods
    if (!strncmp(method, "GET", i))
    {
        ++i;
        // get the requested file name
        unsigned int j = 1;
        char filename[BUF_SIZE];
        filename[0] = '.';
        while(request[i] && request[i] != ' ' && request[i] != '?' && i < BUF_SIZE)
            filename[j++] = request[i++];
        filename[j] = '\0';
        if (filename[j - 1] == '/')
            strcat(filename, "index.html");

        // TODO: check extension/mimetype

        //printf("GET: filename: \"%s\"\n", filename);

        // try to send the file...
        char buf[BUF_SIZE];
        memset(buf, 0, BUF_SIZE);
        FILE *file = fopen(filename, "r");
        if (file)
        {
            // read the file
            fseek(file, 0, SEEK_END);
            size_t sz = ftell(file);
            fseek(file, 0, SEEK_SET);
            char *content = (char *)malloc(sz + 1);
            fread(content, sizeof(char), sz, file);

            // OK, send it to the client
            sprintf(buf, "HTTP/1.0 200 OK\r\n"
                         "Content-Type: text/html\r\n"
                         "Content-Length: %lu\r\n\r\n", sz);
            send(client, buf, strlen(buf), MSG_NOSIGNAL);
            send(client, content, sz, MSG_NOSIGNAL);
            fclose(file);
        }
        else
        {
            // file not found
            sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n"
                         "Content-Type: text/html\r\n"
                         "Content-Length: %lu\r\n\r\n", 19 + strlen(filename));
            send(client, buf, strlen(buf), MSG_NOSIGNAL);
            sprintf(buf, "File \"%s\" not found!\n", filename);
            send(client, buf, strlen(buf), MSG_NOSIGNAL);
        }
    }
    else
        printf("unknown/unimplemented method \"%s\", sorry...\n", method);

    shutdown(client, SHUT_RDWR);
    close(client);

    return 0;
}

void parse(int argc, char* const argv[], char *ip, uint16_t *port, char *dir)
{
    memset(ip, 0, OPT_MAX_SIZE);
    memset(dir, 0, OPT_MAX_SIZE);

    extern char *optarg;
    extern int optind, opterr, optopt;
    int c = -1;
    while ( (c = getopt(argc, argv, "h:p:d:")) != -1)
    {
        switch (c)
        {
            case 'h': strncpy(ip, optarg, OPT_MAX_SIZE); break;
            case 'p': *port = atoi(optarg); break;
            case 'd': strncpy(dir, optarg, OPT_MAX_SIZE); break;
            case '?':
                fprintf(stderr, "error: unknown argument \'%c\'\n", optopt);
                fprintf(stderr, usage, argv[0]);
                exit(1);
        }
    }
}

int set_nonblock(int sd)
{
    int flags;
#ifdef O_NONBLOCK
    if (-1 == (flags = fcntl(sd, F_GETFL, 0)))
        flags = 0;
    return fcntl(sd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctl(sd, FIONBIO, &flags);
#endif
}
