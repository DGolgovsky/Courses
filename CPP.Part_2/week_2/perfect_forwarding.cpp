// lvalue
template<typename T, typename Arg>
unique_ptr<T> make_unique(Arg & arg) {
    return unique_ptr<T>(new T(arg));
}

// rvalue
template<typename T, typename Arg>
unique_ptr<T> make_unique(Arg && arg) {
    return unique_ptr<T>(new T(std::move(arg)));
}

// std::forward for l- and r- values
template<typename T, typename Arg>
unique_ptr<T> make_unique(Arg && arg) {
    return unique_ptr<T>(
            new T(std::forward<Arg>(arg)));
}

// std::forward for lvalue:
{
    X x;
    auto p = make_unique<A>(x);     // Arg = X&

    unique_ptr<A> make_unique(X& && arg) {
        return unique_ptr<A>(new A(std::forward<X&>(arg)));
    }

    X& && forward(remove_reference<X&>::type& a) {
        return static_cast<X& &&>(a);
    }

    // After bonding
    unique_ptr<A> make_unique(X& arg) {
        return unique_ptr<A>(new A(std::forward<X&>(arg)));
    }

    X& forward(X& a) {
        return static_cast<X&>(a);
    }
}

// std::forward for rvalue:
{
    auto p = make_unique<A>(X());       // Arg = X

    unique_ptr<A> make_unique(X&& arg) {
        return unique_ptr<A>(new A(std::forward<X>(arg)));
    }

    X&& forward(remove_reference<X>::type& a) {
        return static_cast<X&&>(a);
    }

    // After bonding
    unique_ptr<A> make_unique(X&& arg) {
        return unique_ptr<A>(new A(std::forward<X>(arg)));
    }

    X&& forward(X& a) {
        return static_cast<X&&>(a);
    }
}
