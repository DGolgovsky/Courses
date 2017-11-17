/*
Выберите функции, при вызове которых обязательно происходит перемещение объекта String (у класса String определены соответствующие перемещающие методы).

Hint: помните, что в теле функции формальный параметр является lvalue вне зависимости от того, как он был передан в функцию.
Answer: 3, 4, 5
*/
#include <iostream>

struct A {
    A() = default;
    A(const A&) { std::cout << "Copy constructor" << std::endl; }
    A& operator=(const A&) { std::cout << "Copy operator=" << std::endl; return *this; }
    A(A&&) { std::cout << "Move constructor" << std::endl; }
    A& operator=(A&&) { std::cout << "Move operator=" << std::endl; return *this; }
};

A & fun1(A & s)
{
    return s;
}

A && fun2(A & s)
{
    return std::move(s);
}

A fun3(A & s)
{
    return std::move(s);
}

A fun4(A s)
{
    return std::move(s);
}

A fun5(A s)
{
    return std::forward<A>(s);
}

A && fun6(A && s)
{
    return std::move(s);
}

A fun7(A && s)
{
    return s;
}

int main() {
    std::cout << "fun1:\n";
    A a;
    A b = fun1(a);
    fun1(a);
    //b = fun1(A());
    
    std::cout << "\nfun2:\n";
    A c;
    A d = fun2(c);
    fun2(c);
    //d = fun2(A());
    
    std::cout << "\nfun3:\n";    
    A e;
    A f = fun3(e);
    fun3(e);
    //f = fun3(A());
    
    std::cout << "\nfun4:\n";    
    A g;
    A h = fun4(A());
    h = fun4(g);
    fun4(A());
    
    std::cout << "\nfun5:\n";    
    A i;
    A j = fun5(A());
    j = fun5(i);
    fun5(A());
    
    std::cout << "\nfun6:\n";    
    A k;
    A l = fun6(A());
    l = fun6(std::move(k));
    fun6(A());
    
    std::cout << "\nfun7:\n";    
    A m;
    A n = fun7(A());
    n = fun7(std::move(m));
    fun7(A());
    
    return 0;
}
