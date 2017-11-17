/*
Напишите шаблонную функцию to_pair, которая принимает произвольный std::tuple и два индекса внутри и возвращает std::pair, содержащий элементы переданного std::tuple с соответствующими индексами.

Пример:

auto t = std::make_tuple(0, 3.5, "Hello");
std::pair<double, char const *> p = to_pair<1,2>(t); 
// p содержит 3.5 и "Hello"

Замечание: реализация должна работать в рамках стандарта C++11.
*/

#include <tuple>
#include <utility>  // std::forward
#include <iostream> // std::cout

template<size_t I1,
         size_t I2,
         typename... Args,
         typename A = typename std::tuple_element<I1, std::tuple<Args...>>::type,
         typename B = typename std::tuple_element<I2, std::tuple<Args...>>::type >
std::pair<A, B> to_pair(std::tuple<Args...>& tuple_)
{
   auto pair_ = std::make_pair(std::get<I1>(tuple_), std::get<I2>(tuple_));
   return pair_;
}

int main()
{
	auto t = std::make_tuple(0, 3.5, "Hello");
	std::pair<double, char const *> p = to_pair<1,2>(t); 
	// p содержит 3.5 и "Hello"
	std::cout << p.first << ", " << p.second << '\n';
	return 0;
}
