int doAsyncWork();

// manual std::thread
#include <thread>
// create thread
std::thread t(doAsyncWork);

// using std::async
#include <future>
std::future<int> fut = std::async(doAsyncWork);
int res = fut.get(); // int -> function return type

// Две стратегии выполнения:
// асинхронное выполнение
// отложенное (синхронное) выполнение
std::launch::async
std::launch::deferred

// Guarantee async
std::future<int> fut = 
    std::async(std::launch::async, doAsyncWork);
int res = fut.get(); // May return exceptions

// Отложенная задача может не выполниться,
// если не будет вызвано get или wait
