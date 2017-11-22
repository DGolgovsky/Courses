#include <list>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

template <typename It, typename Mapper, typename Reducer>
auto map_reduce(It p, It q, Mapper const &f1, Reducer const &f2, size_t threads)
    ->decltype(f1(*p))
{
    using RetType = decltype(f1(*p));

    // Count per thread
    size_t cnt = std::distance(p, q) / threads;

    // Thread function
    auto f = [&f1, &f2](It p, It q, RetType &val) {
        val = f1(*p);
        while (++p != q)
            val = f2(val, f1(*p));
    };

    std::vector<std::pair<std::thread, RetType>> v(threads);
    for (size_t i = 0; i < threads; ++i) {
        It cur = p;
        std::advance(p, cnt);
        if (i < threads - 1)
            v[i].first = std::thread(f, cur, p, std::ref(v[i].second));
        else
            v[i].first = std::thread(f, cur, q, std::ref(v[i].second));
    }

    // Collecting result
    v[0].first.join();
    RetType res = v[0].second;
    for (std::size_t i = 1; i < threads; ++i) {
        v[i].first.join();
        res = f2(res, v[i].second);
    }

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
