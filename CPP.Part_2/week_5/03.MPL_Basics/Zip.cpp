/*
 * Напишите метафункцию Zip (аналог std::transform),
 * которая принимает два списка целых чисел одинаковой длины,
 * а так же бинарную метафункцию, и возвращает список,
 * получившийся в результате поэлементного применения метафункции
 * к соответствующим элементам исходных списков.
 */

#include <iostream>

/* IntList */
template<int ... Ints> struct IntList;
template<int H, int ... T> struct IntList<H, T...>
{
    static int const Head = H;
    using Tail = IntList<T...>;
};
template<> struct IntList<> {};
/* IntList */

/* IntCons */
template<int N, typename IL> struct IntCons;
template<int N, int... Ints> struct IntCons<N, IntList<Ints...>>
{ using type = IntList<N, Ints...>; };
/* IntCons */

// бинарная метафункция
template<int a, int b>
struct Plus
{
    static int const value = a + b;
};

/* Zip */
template< typename IList1,
          typename IList2,
          template <int, int> class Func >
struct Zip
{
    using type = typename IntCons<
            Func<IList1::Head, IList2::Head>::value,
            typename Zip<
                    typename IList1::Tail,
                    typename IList2::Tail,
                    Func>::type >::type;
};
template<template <int, int> class Func>
struct Zip<IntList<>, IntList<>, Func>
{
    using type = IntList<>;
};
/* Zip */

/* Check - Debug function */
template<typename T>
void check()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
/* Check */
int main()
{
    // два списка одной длины
    using L1 = IntList<1,2,3,4,5>;
    using L2 = IntList<1,3,7,7,2>;

    // результат применения — список с поэлементными суммами
    using L3 = Zip<L1, L2, Plus>::type;  // IntList<2, 5, 10, 11, 7>

    check<L3>();

    return 0;
}
