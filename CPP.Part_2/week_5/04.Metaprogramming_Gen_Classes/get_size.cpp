// Example program
#include <iostream>
#include <string>

template <bool condition, typename Type>
struct EnableIf;
 
template <typename Type>
struct EnableIf<true, Type>
{
    using type = Type;
};

template<typename T> struct has_size {
private:  // Спрячем от пользователя детали реализации.
    static int detect(...);  // Статическую функцию и вызывать проще.
    template<typename U> static decltype(std::declval<U>().size(42)) detect(const U&);
public:
    static constexpr bool value = std::is_same<void, decltype(detect(std::declval<T>()))>::value;  // Вот видите, готово.
};

template <typename T>
typename EnableIf<!has_size<T>::value, size_t>::type
get_size(T container)
{
    return container.size();
}
 
template <typename T>
typename EnableIf<has_size<T>::value, size_t>::type
get_size(T value)
{
    return value.size;
}

int main()
{
    std::string s{"Hello"};
    size_t s_size = get_size(s);   // 5, вызывается метод size()
    std::cout << s_size << '\n';
    
    struct Struct {
        size_t size = 0;
    };
    
    Struct x{10};
    size_t x_size = get_size(x);  // 10, читается поле size
    std::cout << x_size << '\n';
    
    return 0;
}

