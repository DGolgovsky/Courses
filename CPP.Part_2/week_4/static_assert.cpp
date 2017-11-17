#include <type_traits>
#include <iostream>

//#define NDEBUG
#include <cassert> // assert

template<class T>
void countdown(T start) {
    // Compile time
    static_assert(std::is_integral<T>::value
               && std::is_signed<T>::value,
                  "Requires signed integral type");
    assert(start >= 0); // Runtime error
    while (start >= 0) {
        std::cout << start-- << std::endl;
    }
}
