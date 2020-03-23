/*
 * Рассмотрим следующую функцию find_if:
 *
 * template<class F>
 * int * find_if(int * p, int * q, F f) {
 *     for ( ; p != q; ++p )
 *         if (f(*p))
 *             return p;
 *     return q;
 * }
 * Определите переменную gen_finder, хранящую безымянную функцию,
 * которая принимает массив значений типа int через два указателя
 * и возвращает безымянную функцию, которая в свою очередь принимает
 * значение типа int и проверяет, есть ли это значение в
 * переданном массиве.
 *
 * Пример:
 * int primes[5] = {2,3,5,7,11};
 * int m[10] = {0,0,1,1,4,6,7,8,9,10};
 *
 * // first_prime будет указывать на число 7
 * int * first_prime = find_if(m, m + 10, gen_finder(primes, primes + 5));
 */

/* my_solution */
auto gen_finder = [](int *p, int *q) {
    return [&](int i) {
        auto m = p;
        auto n = q;
        for ( ; m != n; ++m )
            if (i == *m)
                return i == *m?m:0;
        return (int*)0;
    };
};

/* other solutions */
#include <algorithm>
// определение переменной
auto gen_finder = [](int * p, int * q) { return [p, q](int v) { return std::find(p, q, v) != q; }; };

auto gen_finder = [](const int* const m_begin, const int* const m_end)
{
    return [m_begin, m_end](const int x)
    {
        for (const int* it = m_begin; it != m_end; ++it)
            if (x == *it)
                return true;
        return false;
    };
};

#include <unordered_set>
// определение переменной
auto gen_finder = [](int* a, int* b) {
    std::unordered_set<int> array;
    for (; a!=b; ++a)
        array.emplace(*a);
    return [=](int& x) {
        return array.find(x) != array.end();
    };
};

// определение переменной
#include <functional>
#include <algorithm>
std::function<std::function<bool (int)> (int *, int *)> gen_finder = [] (int * begin, int * end)
{
    return [begin, end] (int value)
    {
        return std::find(begin, end, value) != end;
    };
};

// определение переменной
#include <algorithm>
auto gen_finder = [](int* beg, int* end)
{
    return [beg, end](int x)
    {
        return end != std::find(beg, end, x);
    };
};


