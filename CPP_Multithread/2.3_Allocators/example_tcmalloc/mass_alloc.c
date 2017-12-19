#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "timersub.h"

int main(int argc, char **argv)
{
    struct timeval t1, t2, t3;

    gettimeofday(&t1, NULL);
    for (unsigned int i = 0; i < 100; ++i) {
        int *x = malloc(sizeof(int));
        *x = 123;
    }
    gettimeofday(&t2, NULL);

    timersub(&t2, &t1, &t3);
    printf("=== %ld.%06ld\n", (long int)t3.tv_sec, (long int)t3.tv_usec);

    return 0;
}
