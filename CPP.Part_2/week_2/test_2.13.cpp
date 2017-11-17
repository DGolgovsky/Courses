#include <iostream>
#include <typeinfo>

void print_values(std::ostream const &os)
{
    return;
}

template<typename VType, typename ... Args>
void print_values(std::ostream &os,
                  VType const &value,
                  Args const &... args)
{
    os << typeid(value).name() << ": "
       << value << '\n';
    print_values(os, args...);
}

int main()
{
    print_values(std::cout, 0, 3.5, "Hello");
    print_values(std::cout);
    //print_values();

    return 0;
}
