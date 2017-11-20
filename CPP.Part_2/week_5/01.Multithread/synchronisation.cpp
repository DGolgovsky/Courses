#include <iostream>
#include <thread>
#include <mutex>

double someFunction(int);

double shared = 0;      // shared variable
std::mutex mtx;         // mutex for shared

void compute(int begin, int end) {
    for (int i = begin; i != end; ++i) {
        double current = someFunction(i);
        // Critical section
        std::lock_guard<std::mutex> lck(mtx);
        shared += current;
    }
}

int main()
{
    std::thread th1 (compute, 0,   100);
    std::thread th2 (compute, 100, 200);
    th1.join();
    th2.join();

    std::cout << shared << std::endl;

    return 0;
}
