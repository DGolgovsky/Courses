struct A {
    void foo() { std::cout << "struct A\n"; }
};

struct B {
    /* No foo() method

    void foo() {
        std::cout << "struct B\n";
    }
    */
};

struct C {
    void foo() { std::cout << "struct C\n"; }
};

using Bases = TypeList<A, B, C>;

template<typename TL>
struct inherit;

template<typename... Types>
struct inherit<TypeList<Types...>> : Types... {};

struct D : inherit<Bases>
{
    void foo() { foo_impl<Bases>(); }

    template<typename L> void foo_impl();
};

template<typename L>
inline void D::foo_impl() {
    // Приводим this к указателю на базу из списка
    // Compile-time error without foo() method in base-class B
    static_cast<typename L::Head *>(this)->foo();
    // Рекурсивный вызов для хвоста списка
    foo_impl<typename L::Tail>();
}

template<>
inline void D::fo__impl<TypeList<>>()
{ }
