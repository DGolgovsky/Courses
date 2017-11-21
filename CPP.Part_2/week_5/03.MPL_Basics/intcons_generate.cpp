/* WARNING!
 * Code doen't work
 */
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

// реализация метафункции IntCons
// IntCons позволяет увеличить список на один элемент — он добавляется в начало списка.
template<int H, typename TL>
struct IntCons;

template<int H, int ... Ints>
struct IntCons<H, IntList<Ints...>>
{
    using type = IntList<H, Ints...>;
};

// реализация метафункции Generate
// Generate позволяет сгенерировать список длины N с числами от 0 до N - 1.
// Hint: у метафункции Generate удобно сделать второй параметр со значением по умолчанию.
template<int N, typename T = IntList<0>>
struct Generate;

template<int N, int N2 = 0>
struct Generate<N-1, IntList<N>>
{
    using type = IntList<N>;
};
template<>
struct Generate<0>
{
    using type = IntList<0>;
};

template<typename T>
void check()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    using L1 = IntList<2,3,4>;

    using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>

    using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>

    check<L2>();
    check<L3>();

    return 0;
}
