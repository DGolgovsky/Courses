/*
 * Создайте набор из 16 семафоров SysV с ключем:
 * key_t key = ftok("/tmp/sem.temp", 1);
 * Проинициализируйте их порядковыми номерами [0..15].
 */

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semnum
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    constexpr size_t sem_q = 16;
    key_t key = ftok("/tmp/sem.temp", 1);
    auto sem_id = semget(
            key,
            sem_q,
            IPC_CREAT | 0666
            );
    
    for (size_t i = 0; i < sem_q; ++i) {
        semnum arg;
        
        arg.val = i;
        semctl(sem_id, i, SETVAL, arg);
    }
    
    return 0;
}

