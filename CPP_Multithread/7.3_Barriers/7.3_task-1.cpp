/*
 * Напишите многопоточную программу (POSIX Threads).
 * Должны быть как минимум:
 *  Один поток, ожидающий события по условной переменной.
 *  Один поток, ожидающий достижения барьера.
 * Текст программы должен находиться в файле /home/box/main.cpp
 * PID запущенного процесса должен быть сохранен в файле /home/box/main.pid
 */

#include <iostream>
#include <fstream>
#include <array>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

struct Data
{
    explicit Data(std::size_t n_threads)
        : result{0}
        , calculated{false}
        , cond{PTHREAD_COND_INITIALIZER}
        , mutex{PTHREAD_MUTEX_INITIALIZER}
    {
        pthread_barrier_init(&barrier, nullptr, n_threads);
    }
    
    ~Data() {
        pthread_barrier_destroy(&barrier);
    }
    
    unsigned long result;
    bool calculated;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
};

unsigned long fib(unsigned n)
{
    if (n <= 1) {
        return n;
    }
    
    unsigned long f_prev = 0;
    unsigned long f_cur = 1;
    
    while (--n) {
        auto tmp = f_cur;
        
        f_cur += f_prev;
        f_prev = tmp;
    }
    
    return f_cur;
}

void *thread1_fib_calc(void *arg)
{
    // calculate fibonacci
    Data *dp = static_cast<Data *> (arg);
    
    pthread_mutex_lock(&dp->mutex);
    dp->result = fib(5000000);
    dp->calculated = true;
    pthread_mutex_unlock(&dp->mutex);
    pthread_cond_signal(&dp->cond);
    pthread_barrier_wait(&dp->barrier);
    
    pthread_exit(dp);
}

void *thread2_print_fib(void *arg)
{
    // get the result from the thread 1 and print it
    Data *dp = static_cast<Data *> (arg);
    
    pthread_mutex_lock(&dp->mutex);
    while (!dp->calculated) {
        std::cout << "I'm asleep" << std::endl;
        pthread_cond_wait(&dp->cond, &dp->mutex);
    }
    pthread_mutex_unlock(&dp->mutex);

    std::cout << "Fibonacci number: " << dp->result << std::endl;
    pthread_barrier_wait(&dp->barrier);
    
    pthread_exit(nullptr);
}

void *thread3_print_end(void *arg)
{
    // print that result is
    Data *dp = static_cast<Data *> (arg);
    
    pthread_barrier_wait(&dp->barrier);
    std::cout << "Finished Fibonacci calculation" << std::endl;
    
    pthread_exit(nullptr);
}

int main()
{
    std::ofstream ofs{"main.pid"};
    constexpr std::size_t thread_q = 3;
    std::array<pthread_t, thread_q> threads;
    Data calculation{thread_q};
    
    ofs << getpid() << std::endl;
    pthread_create(&threads[0], nullptr, thread1_fib_calc, &calculation);
    pthread_create(&threads[1], nullptr, thread2_print_fib, &calculation);
    pthread_create(&threads[2], nullptr, thread3_print_end, &calculation);
    
    pthread_join(threads[2], nullptr);
    
    return 0;
}

