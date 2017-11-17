#include <iostream>

struct A {
    A() = default;
    A(const A&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    A& operator=(const A&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
    A(A&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    A& operator=(A&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
};

int main() {
    A a, b;
    b = a;
    b = static_cast<A&>(a);
    b = static_cast<A&&>(a);
    b = std::move(a);
    /* OUTPUT:
     * A& A::operator=(const A&)
     * A& A::operator=(const A&)
     * A& A::operator=(A&&)
     * A& A::operator=(A&&)
     */
    A aa;
    A bb(aa);
    A cc(static_cast<A&>(aa));
    A dd(static_cast<A&&>(aa));
    A ee(std::move(aa));
    /* OUTPUT:
     * A::A(const A&)
     * A::A(const A&)
     * A::A(A&&)
     * A::A(A&&)
     */
    return 0;
}
