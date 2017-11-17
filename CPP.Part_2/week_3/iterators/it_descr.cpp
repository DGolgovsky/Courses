/*
 * Random access iterator: ++, --, arithmetic, <, >, <=, >=
 * (array, vector, deque)
 *
 * Bidirectional iterator: ++, --
 * (list, set, map)
 *
 * Forward iterator: ++
 * (forwared_list, unordered_set, unordered_map)
 *
 * Input iterator: ++, read-only
 *
 * Output iterator: ++, write-only
 */

void   advance (Iterator & it, size_t n); // передвинуть it на n
size_t distance (Iterator f, Iterator l);
void   iter_swap(Iterator i, Iterator j); // swap pointers
std::next(it); // получить следующий за it итератор
std::prev(it); // получить итератор, идущий перед it
