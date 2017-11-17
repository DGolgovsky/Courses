#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char ** argv)
{
    char buf[100];
    size_t sz = 0;

    if (argc != 2) {
        printf("\nPlease call\n\t%s filename\n", argv[0]);
        return 1;
    }

//    int fd = open(argv[1], O_RDONLY);
//    int fd = open(argv[1], O_RDONLY|O_NOFOLLOW); // We don't want open links
    int fd = open(argv[1], O_RDONLY|O_PATH); // Open symbolic links
    perror("fd");
    printf("fd=%d\n", fd);
    sz = read(fd, buf, 100);

    printf("sz=%ld\n", sz);

    return 0;
}
