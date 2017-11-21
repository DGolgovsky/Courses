// Arguments - templates args
// Ret type - type or value
template<typename T>
struct AddPointer
{
    using type = T*;
};

template<int N>
struct Square
{
    static int const value = N * N;
};

