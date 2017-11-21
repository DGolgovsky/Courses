// Calculate list length

#include <iostream>

// Define list
template<typename ... Types>
struct TypeList;

// Specialization by default
template<typename H, typename ... T>
struct TypeList<H, T...>
{
    using Head = H;
    using Tail = TypeList<T...>;
};

// Specialization for empty list
template<>
struct TypeList<> {};

template<typename TL>
struct Length
{
    static int const value = 1 +
        Length<typename TL::Tail>::value;
};

template<>
struct Length<TypeList<>>
{
    static int const value = 0;
};

int main()
{
    using TL = TypeList<double, float, int, char>;
    std::cout << Length<TL>::value << std::endl; // 4

    return 0;
}
