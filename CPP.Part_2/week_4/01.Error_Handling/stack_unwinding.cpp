void foo() {
    D d;
    E e(d);
    if (!e) throw F();
    G g(e); // not create if except
}

void bar() {
    A a;
    try {
        B b;
        foo();
        C c; // not create if except
    } catch (F &f) {
        // Available only A a
        // handling and forwarding
        throw f;
    }
}

