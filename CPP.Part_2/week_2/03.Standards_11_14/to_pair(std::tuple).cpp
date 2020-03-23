#include <tuple>

// принимает std::tuple произвольного размера

// Variant 1
template<size_t i, size_t j, class T>
auto to_pair(T const& t) -> decltype(std::make_pair(std::get<i>(t), std::get<j>(t))) 
{
    return std::make_pair(std::get<i>(t), std::get<j>(t));
}

// Variant 2
template< int I1, int I2, typename TUPLE >
auto to_pair( TUPLE src ) -> 
    std::pair<
         typename std::remove_reference<decltype(std::get<I1>(src))>::type
        ,typename std::remove_reference<decltype(std::get<I2>(src))>::type >
{
    return {std::get<I1>(src),std::get<I2>(src)};
}

// Variant 3
template<int N, int M, typename ... Args>
auto to_pair(std::tuple<Args...> t)
	-> std::pair<typename std::tuple_element<N, std::tuple<Args...>>::type,
				 typename std::tuple_element<M, std::tuple<Args...>>::type>
{
	return std::make_pair(std::get<N>(t), std::get<M>(t));
}
