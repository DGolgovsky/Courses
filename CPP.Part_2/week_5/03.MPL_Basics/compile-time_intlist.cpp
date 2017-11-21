#include <iostream>

// Определение списка целых чисел времени компиляции IntList
// Define list
template<int ... Ints>
struct IntList;

// Specialization by default
template<int H, int ... T>
struct IntList<H, T...>
{
    static int const Head = H;
    using Tail = IntList<T...>;
};

// Specialization for empty list
template<>
struct IntList<> {};

int main()
{
    using primes = IntList<2,3,5,7,11,13>;

    constexpr int head = primes::Head;

    using odd_primes = primes::Tail;

    std::cout << head << '\n';

    return 0;
}
