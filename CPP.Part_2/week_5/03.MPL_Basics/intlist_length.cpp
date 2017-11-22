#include <iostream>
template<int ... Ints> struct IntList;
template<> struct IntList<> {};
template<int H, int ... T>
struct IntList<H, T...>
{
    static int const Head = H;
    using Tail = IntList<T...>;
};

/* Another solution
	template <typename T>
	struct Length;

	template<template<int ...> class IntList, int ...Values>
	struct Length<IntList<Values...>>
	{
	    static const int value = sizeof...(Values);
	};
*/
// Specialization for empty list
template<typename TL>
struct Length
{
    static int const value = 1 +
                             Length<typename TL::Tail>::value;
};

template<>
struct Length<IntList<>>
{
    static int const value = 0;
};

int main()
{
    using primes = IntList<2,3,5,7,11,13>;

    constexpr size_t len = Length<primes>::value; // 6

    std::cout << len << '\n';

    return 0;
}
