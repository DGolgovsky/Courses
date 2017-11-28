// <type_traits>
namespace std {
    template<bool B, class T = void>
        struct enable_if {};

    template<class T>
        struct enable_if<true, T> { using type = T; };
}

template<class T>
typename std::enable_if<
    std::is_integral<T>::value, T>::type
div2(T t) { return t >> 1; }

template<class T>
typename std::enable_if<
    std::is_floating_point<T>::value, T>::type
div2(T t) { return t / 2.0; }

template<class T>
T div2(T t, typename std::enable_if<
    std::is_integral<T>::value, T>::type * = 0)
{ return t >> 1; }

template<class T, class E = typename std::enable_if<
    std::is_floating_point<T>::value, T>::type>
T div2(T t)
{ return t / 2.0; }



template<class T, class E = void>
class A;

template<class T>
class A<T, typename std::enable_if<
        std::is_integral<T>::value>::type>
{};

