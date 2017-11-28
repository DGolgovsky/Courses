typedef char YES;
struct NO { YES m[2]; };

template<bool b>
struct Bool2Type        { using type = YES; };

template<>
struct Bool2Type<false> { using type = NO;  };

template<class T>
struct is_foo_defined
{
    template<class Z, void (Z::*)() = &Z::foo>
        struct wrapper {};

    template<class C>
        static YES check(wrapper<C> * p);

    template<class C>
        static NO  check(...);

    static bool const value =
        sizeof(YES) == sizeof(check<T>(0));
};

template<class L>
void foo_impl()
{
    using Head = typename L::Head;

    constexpr bool has_foo =
        is_foo_defined<Head>::value;

    using CALL =
        typename Bool2Type<has_foo>::type;

    call_foo<Head>(CALL());
    foo_impl<typename L::Tail>();
}

struct D : inherit<Bases>
{
    // ... foo, foo_impl

    template<class Base>
        void call_foo(YES) {
            static_cast<Base *>(this)->foo();
        }

    template<class Base>
        void call_foo(NO) { }
};

