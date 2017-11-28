/* WARNING!
 * Very shitty solution
 */
/*
 * Напишите шаблонную функцию get_size, которая принимает
 * значение некоторого типа, у которого есть
 * либо константный метод size() возвращающий size_t,
 * либо поле size типа size_t,
 * и возвращает соответствующее значение.
 */

#include <iostream>
#include <string>
#include <type_traits>

typedef char YES;
struct NO { YES m[2]; };

template<bool b>
struct Bool2Type        { using type = YES; };

template<>
struct Bool2Type<false> { using type = NO;  };

template <typename T>
class HasSizeMethod {
public:
    static void detect(...);
    template <class U>
    static decltype(std::declval<U>().size()) detect(U&&);

    static constexpr bool value = !std::is_same<void, decltype(detect(std::declval<T>()))>::value;
};

template <typename T>
class HasSizeMethod2 {
public:
    static void detect(...);
    template <class U, typename std::enable_if<true, decltype(std::declval<U>().size())>::type = 0>
    static int detect(U&&);

    static constexpr bool value = std::is_same<int, decltype(detect(std::declval<T>()))>::value;
};

template<class T>
size_t ret_size(YES, T const &val) {
    return val.size();
}

template<class T>
size_t ret_size(NO, T const &val) {
    return val.size;
}

template <typename T>
size_t const get_size(T const &val)
{
    constexpr bool has_size =
            HasSizeMethod<T>::value;
    using CALL = typename Bool2Type<has_size>::type;
    std::cout << "[BOOL]: " << has_size << ", " << typeid(T).name() << '\n';
    return ret_size<T>(CALL(), val);
    
}


int main()
{
    std::cout << std::boolalpha;

    std::string s{"Hello"};
    size_t s_size = get_size(s);   // 5, вызывается метод size()
    std::cout << s_size << " ?= " << s.size() << '\n';

    struct Damn {
        explicit Damn(size_t value) : size(value) {};
        size_t size = 0;
    };

    Damn x{10};
    size_t x_size = get_size(x);  // 10, читается поле size
    std::cout << x_size << " ?= " << x.size << '\n';

    return 0;
}

