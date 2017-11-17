#include <typeinfo>
#include <iostream>

struct Unit
{
    virtual ~Unit()
    {}
};

struct Elf: Unit
{
};

int main()
{
    Elf e;
    Unit &ur = e;
    Unit *up = &e;

    using std::cout;
    using std::endl;
    cout << typeid(ur) .name() << endl;  // Elf
    cout << typeid(*up).name() << endl;  // Elf
    cout << typeid(up) .name() << endl;  // Unit *
    cout << typeid(Elf).name() << endl;  // Elf
    cout << (typeid(ur) == typeid(Elf)); // 1

    return 0;
}
