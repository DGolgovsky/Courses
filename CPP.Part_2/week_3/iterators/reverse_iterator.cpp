list<int> l = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// list<int>::reverse_iterator
for (auto i = l.rbegin(); i != l.rend(); ++i)
    cout << *i << endl;

list<int>::iterator i = l.begin();
advance(i, 5); // i point to 5
// ri point to 4
list<int>::reverse_iterator ri = i;
i = ri.base();

// <iterator>
template <class Iterator>
class reverse_iterator {...};

