/*
 * set хранит упорядоченное множество (как двоичное дерево поиска)
 * Добавление, удаление и поиск работают за O(log n)
 * Хранящиеся значения не изменяемы
 */

#include <set>

std::set<int> primes = {2, 3, 5, 7, 11};
// Дальнейшее заполнение
if (primes.find(173) != primes.end())
    std::cout << 173 << "is prime\n";

// std::pair<iterator, bool>
auto res = primes.insert(3);

// В multiset хранится упорядоченное мультимножество
std::multiset<int> fib = {0, 1, 1, 2, 3, 5, 8};
// return iterator       lb=^ ub= ^
auto lb = fib.lower_bound(1);
auto ub = fib.upper_bound(1);
// iterator
auto res = fib.insert(13);
// pair<iterator, iterator>
auto eq = fib.equal_ranfe(1);

