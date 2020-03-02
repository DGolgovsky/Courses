/* Requires C++11 */
#include "type.hpp"
#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

/* If uses C++98 */
/*
struct handle
{
    char *p;
    handle(char* ptr) : p(ptr) {}
    ~handle() {
        std::free(p);
    }
};
*/

std::string demangle(char const *name)
{
    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable C++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
            std::free
    };
/*
    handle result(abi::__cxa_demangle(name, NULL, NULL, &status));

    return (status == 0) ? result.p : name;
*/
    return (status == 0) ? res.get() : name;
}

#else

// does nothing if not g++
std::string demangle(char const *name)
{
    return name;
}

#endif
