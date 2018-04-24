/*
 * Общая память SysV.
 *
 * Создайте общую память SysV
 * (не менее 1 мегабайта) с ключем:
 *
 * key_t key = ftok("/tmp/mem.temp", 1);
 *
 * Каждый байт первого мегабайта
 * общей памяти заполните числом 42.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHMSIZE 1024*1024

void shmrm(void* addr)
{
    if (-1 == shmdt(addr)) {
        perror("shmdt");
        exit(1);
    }
}

int main(void)
{
    int shmid;
    key_t key = ftok("/tmp/mem.temp", 1);
    
    if (-1 == (shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666))) {
        perror("shmget");
        return -1;
    }

    char *addr;
    if ((char*) -1 == (addr = shmat(shmid, NULL, 0))) {
        perror("shmat");
        shmrm(addr);
    }

    int i = 0;
    for(; i < SHMSIZE; ++i) {
        *start++ = 42;
    }

    sleep(10);
    shmrm(addr);

    return 0;
}

