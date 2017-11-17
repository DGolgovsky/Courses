#include <algorithm>
#include <iterator>

template<class FwdIt>
FwdIt remove_nth(FwdIt start, FwdIt end, size_t n) {
    return std::remove_if (start, end, 
        [&n](typename std::iterator_traits<FwdIt>::reference val) {
            return (n-- == 0);
        } );
}


