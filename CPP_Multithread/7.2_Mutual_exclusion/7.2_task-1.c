#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define restrict __restrict

int count = 0; // mutexes -1;
int flag = 1;
int check = 0;

void
change_cnt(pthread_mutex_t * restrict mx)
{
    int i;
    pthread_mutex_lock(mx);
    flag = (flag == 1) ? -1 : 1;
    for(i = 0; i < 50; ++i)
    {
        count += flag;
        usleep(5000);
    }
    pthread_mutex_unlock(mx);
}

void
change_cnt_sp(pthread_spinlock_t * restrict sp)
{
    int i;
    for(i = 0; i < 50; ++i)
    {
        pthread_spin_lock(sp);
        flag = (flag == 1) ? -1 : 1;
        count += flag;
        usleep(5000);
        pthread_spin_unlock(sp);
    }
}

void
change_cnt_rw(pthread_rwlock_t * restrict rw)
{
    int i;
    pthread_rwlock_wrlock(rw);
    flag = (flag == 1) ? -1 : 1;
    for(i = 0; i < 50; ++i)
    {
        count += flag;
    }
    pthread_rwlock_unlock(rw);
}

void*
threadmx(void* arg)
{
    int error;
    pthread_mutex_t* mx = (pthread_mutex_t*) arg;
    error = pthread_mutex_trylock(mx);
    if(EBUSY == error)
    {
        printf("mutex has been locked\n");
        change_cnt(mx);
    }
    else
    {
        pthread_mutex_unlock(mx);
        change_cnt(mx);
    }
    pthread_exit(NULL);
}

void*
threadsp(void* arg)
{
    int error;
    pthread_spinlock_t* sp = (pthread_spinlock_t*) arg;
    error = pthread_spin_trylock(sp);
    if(error == EBUSY)
    {
        printf("spinlock hasb been locked\n");
        change_cnt_sp(sp);
    }
    else
    {
        pthread_spin_unlock(sp);
        change_cnt_sp(sp);
    }
    pthread_exit(NULL);
}

void*
threadrw(void* arg)
{
    pthread_rwlock_t* rw = (pthread_rwlock_t*) arg;

    change_cnt_rw(rw);
    
    usleep(2500);
    pthread_exit(NULL);
}

void
mywait_mutex(pthread_mutex_t * restrict mx)
{
    int i;
    int const threads_cnt = 10;
    pthread_t tids[threads_cnt];

    for(i = 0; i < threads_cnt; ++i)
    {
        pthread_create(&tids[i], 0, threadmx, mx);
    }

    for(i = 0; i < threads_cnt; ++i)
    {
        pthread_join(tids[i], NULL);
    }

    pthread_mutex_destroy(mx);
}

void
mywait_spinlock(pthread_spinlock_t * restrict sp)
{
    int i;
    int const threads_cnt = 10;
    pthread_t tids[threads_cnt];

    for(i = 0; i < threads_cnt; ++i)
    {
        pthread_create(&tids[i], 0, threadsp, (void*) sp);
    }

    for(i = 0; i < threads_cnt; ++i)
    {
        pthread_join(tids[i], NULL);
    }

    pthread_spin_destroy(sp);
}

void
mywait_rwlock(pthread_rwlock_t * restrict rw)
{
    int i;
    int const threads_cnt = 10;
    pthread_t tids[threads_cnt];

    for(i = 0; i < threads_cnt; ++i)
    {
        pthread_create(&tids[i], 0, threadrw, rw);
    }

    for(i = 0; i < threads_cnt; ++i)
    {
        pthread_rwlock_rdlock(rw);
        printf("rwlock count = %d ", count);
        usleep(10000);
        printf("and %d\n", count);
        pthread_rwlock_unlock(rw);
        pthread_join(tids[i], NULL);
    }
    
    pthread_rwlock_destroy(rw);
}

int
main(void)
{
    pthread_mutex_t mx;
    pthread_spinlock_t sp;
    pthread_rwlock_t rw;

    FILE* f = fopen("/home/box/main.pid", "w+");
    fprintf(f, "%d", (int) getpid());
    fclose(f);

    if(0 == pthread_mutex_init(&mx, NULL))
    {
        mywait_mutex(&mx);
        ++check;
    }

    if(0 == pthread_spin_init(&sp, PTHREAD_PROCESS_PRIVATE))
    {
        mywait_spinlock(&sp);
        ++check;
    }

    if(0 == pthread_rwlock_init(&rw, NULL))
    {
        mywait_rwlock(&rw);
        ++check;
    }

    printf("check=%d\n", (check == 3) ? count : -1);

    return 0;
}
