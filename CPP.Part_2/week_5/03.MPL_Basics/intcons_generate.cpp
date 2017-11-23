#include <iostream>

//шаблон пустых и не пустых списков
template<int ...Ints>
struct IntList;

//явная специализация с выделением первого элемента списка
template<int N, int ...Ints>
struct IntList<N, Ints...> {
    static const int Head = N;
    using Tail = IntList<Ints...>;
};

//явная специализация пустого списка
template<>
struct IntList<>{};

// реализация метафункции IntCons
// IntCons позволяет увеличить список на один элемент — он добавляется в начало списка.
template<int N, typename IL> struct IntCons;

template<int N, int... Ints> struct IntCons<N, IntList<Ints...>>
{ using type = IntList<N, Ints...>; };

// реализация метафункции Generate
// Generate позволяет сгенерировать список длины N с числами от 0 до N - 1.
// Hint: у метафункции Generate удобно сделать второй параметр со значением по умолчанию.
template<class S> struct next_integer_sequence;

template<int... Ints>
struct next_integer_sequence<IntList<Ints...>>
{
    using type = IntList<Ints..., sizeof...(Ints)>;
};

template<int I, int N>
struct make_int_seq_impl
{
    using type = typename next_integer_sequence<
            typename make_int_seq_impl<I+1, N>::type>::type;
};

template<int N> struct make_int_seq_impl<N, N>
{
    using type = IntList<>;
};

template<int N, int I = 0>
struct Generate {
    using type = typename make_int_seq_impl<I, N>::type;
};

template<typename T>
void check()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    using L1 = IntList<2, 3, 4>;

    using L2 = IntCons<1, L1>::type;   // IntList<1,2,3,4>

    using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>

    check<L1>();
    check<L2>();
    check<L3>();

    return 0;
}
