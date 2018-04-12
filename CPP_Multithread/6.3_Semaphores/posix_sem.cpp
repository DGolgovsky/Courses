/*
 * Создайте семафор POSIX с именем:
 * /test.sem
 * Проинициализируйте его числом 66.
 */

#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int main()
{
    sem_t *semid = sem_open(
            "/test.sem",
            O_CREAT,
            0666,
            66
        );
    
    int val;
    
    sem_getvalue(semid, &val);
    std::cout << val << std::endl;
    
    return 0;
}

