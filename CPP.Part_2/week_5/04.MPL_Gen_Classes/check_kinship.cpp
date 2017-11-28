typedef char YES;
struct NO { YES m[2]; };

template<class B, class D>
struct is_base_of
{
    static YES test(B *);
    static NO  test(...);

    static bool const value =
        sizeof(YES) == sizeof( test( (D *)0 ) );
};

template<class D>
struct is_base_of<D, D>
{
    static bool const value = false;
};

