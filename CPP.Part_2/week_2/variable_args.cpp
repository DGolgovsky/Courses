#include <iostream>

void printf(char const *s)
{
    while (*s) {
        if (*s == '%' && *(++s) != '%')
            // Handle error in runtime
            // %* > args
        std::cout << *s++;
    }
}

template<typename T, typename ... Args>
void printf(char const *s, T value, Args ... args)
{
    while (*s) {
        if (*s == '%' && *(s++) != '%') {
            std::cout << value;
            printf(++s, args...);
            return;
        }
        std::cout << *s++;
    }
    // Handle error in runtime
    // %* < args
}

