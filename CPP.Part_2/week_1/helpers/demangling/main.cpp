#include <iostream>
#include "type.hpp"

struct Base
{
    virtual ~Base() {}
};

struct Derived : public Base
{

};

int main()
{
    Base* ptr_base = new Derived(); // Please use smart pointers in YOUR code!
    std::cout << "Type of ptr_base: " << type(ptr_base) << std::endl;

    std::cout << "Type of pointee: " << type(*ptr_base) << std::endl;

    delete ptr_base;

    return 0;
}
