template<class T>
struct is_foo_defined
{
    // обёртка, которая позволит проверить
    // наличие метода foo с заданной сигнатурой
    template<class Z, void (Z::*)() = &Z::foo>
        struct wrapper {};

    template<class C>
        static YES check(wrapper<C> * p);

    template<class C>
        static NO  check(...);

    static bool const value =
        sizeof(YES) == sizeof(check<T>(0));
};
