#include <iostream>
#include <tuple>

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

template<class S> struct next_integer_sequence;

template<int... Ints> struct next_integer_sequence<IntList<Ints...>>
{ using type = IntList<Ints..., sizeof...(Ints)>; };

template<int I, int N> struct make_int_seq_impl
{ using type = typename next_integer_sequence<
            typename make_int_seq_impl<I+1, N>::type>::type; };

template<int N> struct make_int_seq_impl<N, N>
{ using type = IntList<>; };

template<int N, int I = 0> struct Generate
{ using type = typename make_int_seq_impl<I, N>::type; };

template<typename T> void check()
{ std::cout << __PRETTY_FUNCTION__ << std::endl; }
/************************/

template<typename F, typename T>
auto apply(F f, T const &tpl)
    -> decltype(f(tpl))
{
    return f(tpl);
}

/************************/
int main()
{
    using L1 = IntList<2, 3, 4>;
    using L3 = Generate<5>::type;      // IntList<0,1,2,3,4>

    auto f = [](int x, double y, double z) { return x + y + z; };
    auto t = std::make_tuple(30, 5.0, 1.6);  // std::tuple<int, double, double>
    auto res = apply(f, t);                // res = 36.6
    check<L1>();
    check<L3>();
    std::cout << res << std::endl;

    return 0;
}
