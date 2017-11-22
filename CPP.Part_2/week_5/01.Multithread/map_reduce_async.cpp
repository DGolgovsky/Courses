#include <future>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

template<typename It, typename Mapper, typename Reducer>
auto map_reduce(It p, It q, Mapper f1, Reducer f2,  size_t threads)
-> decltype(f1(*p))
{
    using RetType = decltype(f1(*p));

    // Count per thread
    size_t cnt = std::distance(p, q) / threads;

    // Thread function
    auto f = [&f1, & f2](It p, It q) {
        RetType res = f1(*p);
        while (++p != q)
            res = f2(res, f1(*p));
        return res;
    };

    auto arr_futures = new std::future<RetType>[threads];
    for (size_t i = 0; i < threads; ++i) {
        It cur = p;
        std::advance(p, cnt);
        if (i < threads - 1)
            arr_futures[i] = std::async(std::launch::async, f, cur, p);
        else
            arr_futures[i] = std::async(std::launch::async, f, cur, q);
    }

    // Collecting result
    auto res = arr_futures[0].get();
    for (size_t i = 1; i < threads; ++i)
        res = f2(res, arr_futures[i].get());
    delete [] arr_futures;

    return res;
}

int main()
{
    std::list<int> l = {1,2,3,4,5,6,7,8,9,10};
    // параллельное суммирование в 3 потока
    auto sum = map_reduce(l.begin()
            ,l.end()
            ,[](int i){ return i; }
            ,std::plus<int>(), 3);

    std::cout << sum << std::endl;
    // проверка наличия чётных чисел в четыре потока
    auto has_even = map_reduce(l.begin(), l.end(),
                               [](int i){return i % 2 == 0;},
                               std::logical_or<bool>(), 4);

    std::cout << has_even << std::endl;
    return 0;
}
