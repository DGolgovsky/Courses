/*
 * unordered_set хранит множество как хеш-таблицу
 * Добавление, удаление и поиск работают за O(1) в среднем
 * Хранящиеся значения не изменяемы
 * equal_range, reserve
 */

#include <unordered_set>

unordered_set<int> primes = {2, 3, 5, 7, 11};
// Fill
if (primes.find(173) != primes.end())
    std::cout << 173 << " is prime\n";

// std::pair<iterator, bool>
auto res = primes.insert(3);

unordered_multiset<int> fib = {0, 1, 1, 2, 3, 5, 8};
// iterator
auto res = fib.insert(13);

