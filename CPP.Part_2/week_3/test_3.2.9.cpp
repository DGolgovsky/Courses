/*
 * Для последовательности s1,s2,s3,…,sn−1,sns1,s2,s3,…,sn−1,sn будем
 * называть подотрезком подпоследовательность вида
 * si,si+1,si+2,…,sj−2,sj−1si,si+1,si+2,…,sj−2,sj−1 для некоторых
 * ii и jj, i≤ji≤j, т.е. подотрезок — это непрерывная
 * подпоследовательность.
 *
 * Напишите функцию max_increasing_len, которая принимает
 * последовательность, хранящуюся в std::list, по двум итераторам,
 * и вычисляет для неё длину самого длинного строго возрастающего
 * подотрезка.
 *
 * Пример:
 * std::list<int> const l1 = {7,8,9,4,5,6,1,2,3,4};
 * size_t len1 = max_increasing_len(l1.begin(), l1.end());
 * // 4, соответствует подотрезку 1,2,3,4
 *
 * std::list<int> const l2 = {-3,-2,-1,0,0,1,2,3,4,5};
 * size_t len2 = max_increasing_len(l2.begin(), l2.end());
 * // 6, соответствует подотрезку 0,1,2,3,4,5
 *
 * Ограничения: не используйте другие контейнеры,
 * не копируйте элементы из списка.
 */
// Example program
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
template<class ForwardIt>
ForwardIt sorted_until(ForwardIt first, ForwardIt last)
{
    if (first != last) {
        ForwardIt next = first;
        while (++next != last) {
            if (*next < *first)
                return next;
            if (*next == *first)
                return next;
                            std::cout << "first=" << *first << ", "
                  << "next=" << *next << "\n";
            first = next;

        }
    }
    return last;
}
template<typename It>
size_t max_increasing_len(It p, It q)
{
    std::pair<It,It> pr = std::make_pair( p, p );

    for ( auto first = p; first != q; )
    {
        auto last = sorted_until<It>( first, q );
 //       std::cout << "first=" << *first << ", "
 //                 << "last=" << *last << "\n";
        if ( std::distance( pr.first, pr.second ) < std::distance( first, last ) )
        {
            pr = { first, last };
        }
        first = last;


    }

    return std::distance( pr.first, pr.second );
}

int main()
{
    std::list<int> const l1 = {7,8,9,4,5,6,1,2,3,4};
    size_t len1 = max_increasing_len(l1.begin(), l1.end()); // 4, соответствует подотрезку 1,2,3,4
    std::cout << len1 << '\n';
    std::list<int> const l2 = {-3,-2,-1,0,0,1,2,3,4,5};
    size_t len2 = max_increasing_len(l2.begin(), l2.end()); // 6, соответствует подотрезку 0,1,2,3,4,5
    std::cout << len2 << '\n';

    return 0;
}

