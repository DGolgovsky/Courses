#include <boost/type_traits.hpp>

template <typename T>
struct is_void : public boost::false_type {};
template <>
struct is_void<void> : public boost::true_type {};

template <typename T>
struct is_pointer: public boost::false_type {};
template <typename T>
struct is_pointer<T*> : public boost::true_type {};

template <typename I1, typename I2, bool b>
I2 copy_imp(I1 first, I1 last, I2 out,
        const boost::integral_constant<bool, b>&) {
    while (first != last) {
        *out = *first;
        ++out; ++first;
    }
    return out;
}

template <typename T>
T* copy_imp(const T* first, const T* last, T* out,
            const boost::true_type&) {
    memmove(out, first, (last - first) * sizeof(T));
    return out + (last - first);
}

template <typename I1, typename I2>
inline I2 copy(I1 first, I1 last, I2 out) {
    typedef typename std::iterator_traits<I1>::
                     value_type value_type;
    return copy_imp(first, last, out,
           boost::has_trivial_assign<value_type>());
}

template <class T>
void do_destroy_array(T* first, T* last,
                      const boost::false_type&) {
    while (first != last) {
        first->~T();
        ++first;
    }
}

template <class T>
inline void do_destroy_array(T* first, T* last,
                             const boost::true_type&) { }

template <class T>
inline void destroy_array(T* p1, T* p2) {
    do_destroy_array(p1, p2, boost::has_trivial_destructor<T>());
}

int main(void)
{
    return 0;
}

