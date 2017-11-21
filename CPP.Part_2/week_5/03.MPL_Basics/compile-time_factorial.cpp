// May be realised via constexpr

#include <iostream>

template<int N>
struct Fact
{
    static int const
        value = N * Fact<N - 1>::value;
};

template<>
struct Fact<0>
{
    static int const value = 1;
};

int main()
{
    std::cout << Fact<10>::value << std::endl;

    return 0;
}
