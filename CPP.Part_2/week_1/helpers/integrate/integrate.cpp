#include <iostream>
#include <cmath>
 
// подключаем библиотеку pthread
#include <pthread.h>
 
// функция создания потоков имеет следующую сигнатуру
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                    void *(*start_routine) (void *), void *arg);
 
// структура для хранения данных о задаче интегрирования
struct Task
{
    // функция
    double (*f) (double);
     
    // начальная точка отрезка
    double start;
 
    // конечная точка отрезка
    double end;
     
    // шаг интегрирования
    double eps;
 
    // куда записать результат
    double * result;
};
 
// функция потока
void * thread_fun(void * data)
{
    // получаем задачу
    Task & t = *static_cast<Task *>(data);
     
    // переменная для результата
    double res = 0;
     
    for (double x = t.start; x < t.end; x += t.eps)
        res += t.f(x + t.eps / 2) * t.eps;
     
    *t.result = res;
    return 0;
}
 
// функция, которую будем интегрировать
double function(double x)
{
    return exp(x * sin(x));
}
 
int main( )
{
    // количество потоков
    int const THREAD_COUNT = 8;
 
    // массив, в который будут записаны результаты
    double results[THREAD_COUNT] = {};
 
    // задачи для потоков
    Task tasks[THREAD_COUNT] = {};
 
    // пределы интегрирования
    double const start = -5;
    double const end   =  5;
 
    // заполняем задачи
    double const taskLen = (end - start) / THREAD_COUNT;
    for (int i = 0; i != THREAD_COUNT; ++i)
    {
        tasks[i].f      = &function;
        tasks[i].start  = start + taskLen * i;
        tasks[i].end    = tasks[i].start + taskLen;
        tasks[i].eps    = 1e-7;
        tasks[i].result = &results[i];
    }
    // создаём дескрипторы потоков
    pthread_t threads[THREAD_COUNT];
 
    // создаём и запускаем потоки
    for (size_t i = 0; i != THREAD_COUNT; ++i)
        pthread_create(&threads[i], 0, &thread_fun, &tasks[i]);
 
    // дожидаемся завершения потоков
    for (size_t i = 0; i != THREAD_COUNT; ++i)
        pthread_join(threads[i], 0);
 
    // складываем результаты
    double res = 0;
 
    for (size_t i = 0; i != THREAD_COUNT; ++i)
        res += results[i];
    // выводим результат
    std::cout << "Result: " << res << std::endl;
 
    return 0;
}
