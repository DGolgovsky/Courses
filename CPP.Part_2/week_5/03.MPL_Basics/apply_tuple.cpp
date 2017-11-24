/*
 * Воспользуйтесь IntList и метафункцией Generate для того,
 * чтобы научиться "раскрывать" кортежи.
 * От вас потребуется написать функцию apply, которая
 * принимает функтор и кортеж с аргументами для вызова этого функтора
 * и вызывает функтор от этих аргументов.
*/

#include <tuple>
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

/* Generate */
template<int N, typename T> struct IntCons;
template<int N, int ...L> struct IntCons<N, IntList<L...>>
{ using type = IntList<N, L...>; };
template<int N, int K = 0> struct Generate
{ using type = typename IntCons<K, typename Generate<N - 1, K + 1>::type>::type; };
template<int K> struct Generate<1, K>
{ using type = IntList<K>; };
template<> struct Generate<0>
{ using type = IntList<>; };
/* Generate */

/* apply */
template<typename F, typename T, int ...Ints>
auto callFunc(F& f, T const& tpl, IntList<Ints...>)
    -> decltype(f(std::get<Ints>(tpl)...))
{
    return f(std::get<Ints>(tpl)...);
};
template<typename F, typename ...Args>
auto apply(F &f, std::tuple<Args...> const& tpl)
    -> decltype(callFunc(f, tpl, typename Generate<sizeof ...(Args)>::type()))
{
    return callFunc(f, tpl, typename Generate<sizeof ...(Args)>::type());
};
/* apply */

int main()
{
    auto f = [](int x, double y, double z) { return x + y + z; };
    auto t = std::make_tuple(30, 5.0, 1.6); // std::tuple<int, double, double>
    auto res = apply(f, t); // res = 36.6

    std::cout << res << std::endl;

    return 0;
}
