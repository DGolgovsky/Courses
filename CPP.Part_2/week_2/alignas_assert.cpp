#include <type_traits>

alignas(float) unsigned char c[sizeof(float)];

template<class T>
void run(T *data, size_t n)
{
    static_assert(std::is_signed<T>::value, // Compile error if T unsigned
                  "T is not signed.");
}
