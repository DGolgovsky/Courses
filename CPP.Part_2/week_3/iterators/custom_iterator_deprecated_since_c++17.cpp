// <iterator>
template
< class Category,               // iterator::iterator_category
  class T,                      // iterator::value_type
  class Distance = ptrdiff_t,   // iterator::difference_type
  class Pointer = T*,           // iterator::pointer
  class Reference = T&          // iterator::reference
> class iterator;

//////////

#include <iterator>

struct PersonIterator
    : std::iterator<forward_iterator_tag, Person>
{
    // operator++, operator*, operator->, ...
};

