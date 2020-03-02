#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <typeinfo>

std::string demangle(char const *name);

template <class T>
std::string type(T const &t)
{
    return demangle(typeid(t).name());
}

#endif
