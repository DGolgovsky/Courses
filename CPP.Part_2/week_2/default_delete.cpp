struct SomeType
{
    SomeType() = default; // Default constructor
    SomeType(OthreType value);
};

struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable & operator=(const NonCopyable&) = delete;
}

template<class T>
void foo(T const *p) { /* ... */ }

void foo(char const *) = delete;
