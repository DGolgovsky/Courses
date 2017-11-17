// <iterator>
struct random_access_iterator_tag {};
struct bidirectional_iterator_tag {};
struct forward_iterator_tag {};
struct input_iterator_tag {};
struct output_iterator_tag {};

template<class I>
void advance(I &i, size_t n,
             random_access_iterator_tag)
{
    i+= n;
}

template<class I>
void advance(I &i, size_t n, ...) {
    for (size_t k = 0; k != n; ++k, ++i);
}

template<class I>
void advance(I & i, size_t n) {
    advance(i, n, typename iterator_traits<I>::iterator_category());
}
