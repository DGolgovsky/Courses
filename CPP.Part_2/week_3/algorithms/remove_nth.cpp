/*
 * Напишите алгоритм remove_nth, который удаляет элемент из
 * последовательности по номеру этого элемента.
 *
 * Пример:
 * std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
 * v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
 * // теперь в v = {0,1,2,3,4,6,7,8,9,10};
 */

// Example program
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
template <typename ForwardIt>
ForwardIt remove_nth(ForwardIt first, ForwardIt last, size_t value) {
    if (std::distance(first, last) < value)
        return last;
	std::advance(first, value);
	if (first != last) {
		ForwardIt dest = first;
		return std::move(++first, last, dest);
	}
	return last;
}

int main()
{
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
    v.erase(remove_nth(v.begin(), v.end(), 5), v.end());
    // теперь в v = {0,1,2,3,4,6,7,8,9,10};
    for (auto it : v)
        std::cout << it << ",";
    std::cout << '\n';
    
    std::list<int> l = {1,2,3,4};
    l.erase(remove_nth(l.begin(), l.end(), 5), l.end());
    for (auto it : l)
        std::cout << it << ",";
    std::cout << '\n';

    return 0;
}

