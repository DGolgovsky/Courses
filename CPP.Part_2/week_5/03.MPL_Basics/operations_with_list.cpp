// Add element into begin
template<typename H, typename TL>
struct Cons;

template<typename H, typename ... Types>
struct Cons<H, TypeList<Types...>>
{
    using type = TypeList<H, Types...>;
};

// Concatenation lists
template<typename TL1, typename TL2>
struct Concat;

template<typename... Ts1, typename... Ts2>
struct Concat<TypeList<Ts1...>, TypeList<Ts2...>>
{
    using type = TypeList<Ts1..., Ts2...>;
};

