template <typename T> struct has_typedef_foobar {
    typedef char yes[1];    // sizeof(yes) == 1
    typedef char no [2];    // sizeof(no) == 2

    template <typename C>
        static yes& test(typename C::foobar*);
    template <typename> static no& test(...);
    static const bool value =
        sizeof(test<T>(0)) == sizeof(yes);
};

struct foo { typedef float foobar; };

// has_typedef_foobar<int>::value == false
// has_typedef_foobar<foo>::value == true
