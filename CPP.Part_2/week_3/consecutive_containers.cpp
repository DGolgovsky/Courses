/* Generic Methods:
 * Конструктор от двух итераторов
 * Конструктор от count и defVal
 * Конструктор от std::initializer_list<T>
 * Методы back, front
 * Методы push_back, emplace_back
 * Методы assign
 * Методы insert
 * Методы emplace
 * Методы erase от одного или двух итераторов
 */

/* vector */
/*
 * operator[], at,
 * resize,
 * capacity, reserve, shrink_to_fit,
 * pop_back,
 * data.
 */
#include <vector>

std::vector<std::string> v = {"One", "Two"};
v.reserve(100);
v.push_back("Three");
v.emplace_back("Four");
legacy_function(v.data(), v.size());
std::cout << v[2] << std::endl;

/* vector hints:*/
std::vector<int> &v = getData();
// shrink_to_fit
std::vector<int>(v).swap(v);
// clear + shrink_to_fit
std::vector<int>().swap(v);

/* deque */
/*
 * operator[], at,
 * resize,
 * push_front, emplace_front
 * pop_back, pop_front,
 * shrink_to_fit.
 */
#include <deque>

std::deque<std::string> d = {"One", "Two"};
d.emplace_back("Three");
d.emplace_front("Zero");
std::cout << d[1] << std::endl;

/* list */
/*
 * push_front, emplace_front,
 * pop_back, pop_front,
 * splice,
 * merge, remove, remove_if, reverse,
 * sort, unique.
 */
#include <list>

std::list<std::string> l = {"One", "Two"};
l.emplace_back("Three");
l.emplace_front("Zero");
std::cout << l.front() << std::endl;

for(std::string &s : l)
    std::cout << s << std::endl;

std::list<std::string>::iterator it = l.begin();
for( ; it != l.end(); ++it) {
    if (*it == "Two")
        break;
}
l.erase(it);

auto last = l.end();
--last; // last element

