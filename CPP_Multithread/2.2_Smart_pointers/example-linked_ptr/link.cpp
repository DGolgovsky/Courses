#include <iostream>
#include <memory>

struct B;

struct A {
    int value;
    std::shared_ptr<B> b;
    A() { std::cout << "A()" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }

};

struct B {
    int value;
    //std::shared_ptr<A> a;
    std::weak_ptr<A> a; // <-- lnk_counter not incremented
    B() { std::cout << "B()" << std::endl; }
    ~B() { std::cout << "~B()" << std::endl; }

};

int main(int argc, char **argv)
{
    std::shared_ptr<A> a(new A());
    std::shared_ptr<B> b(new B());

    a->b = b; // <-- link_counter == 1
    b->a = a;

    a->value = 123;
    {
        std::shared_ptr<A> aa = b->a.lock(); // "Temporary"
        //std::cout << b->a->value << std::endl; // Used with B::shared_ptr
        std::cout << aa->value << std::endl;
    }

    return 0;
}
