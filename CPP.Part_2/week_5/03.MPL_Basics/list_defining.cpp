// Define list
template<typename ... Types>
struct TypeList;

// Specialization by default
template<typename H, typename ... T>
struct TypeList<H, T...>
{
    using Head = H;
    using Tail = TypeList<T...>;
};

// Specialization for empty list
template<>
struct TypeList<> {};

