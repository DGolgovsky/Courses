/*
 * std::set - множество.
 * Документация: http://www.cplusplus.com/reference/set/set/
 *
 * std::multiset - мультимножество.
 * Документация: http://www.cplusplus.com/reference/set/multiset/
 *
 * std::map - ассоциативный массив, словарь,
 * упорядоченный список пар "ключ-значение".
 * Документация: http://www.cplusplus.com/reference/map/map/
 *
 * std::multimap - упорядоченный список пар "ключ-значение"
 * с повторениями ключей.
 * Документация: http://www.cplusplus.com/reference/map/multimap/
 *
 * Все эти контейнеры реализованы с помощью красно-черных деревьев.
 *
 * Подробнее:
 * О 2-3 деревьях на английской википедии:
 * https://en.wikipedia.org/wiki/2-3_tree
 * О красно-черных деревьях на английской википедии:
 * https://en.wikipedia.org/wiki/Red-black_tree
 *
 * Дополнительно можно разобраться с B-деревьями и AVL-деревьями.
 * Почитать можно тут:
 * B-дерево: https://en.wikipedia.org/wiki/B-tree
 * B+-дерево: https://en.wikipedia.org/wiki/B%2B_tree
 * AVL-дерево: https://en.wikipedia.org/wiki/AVL_tree
 *
 * А также имеет смысл попробовать следующие библиотеки:
 * https://code.google.com/p/cpp-btree/
 * http://adtinfo.org/
 */

#include <set>
#include <multiset>
#include <map>
#include <multimap>

int main()
{

    // 8 3 10 1 6 4 7 14 13
    //          8 - root
    //      3       10
    //    1   6        14
    //   4      7    13

    //     2 tree
    //          [p]
    //      <=p     >p

    //      2-3 tree
    //        [p q]
    // [<=p] [>p <=q] [>q]

    std::set<int> s; // sorted, binary-tree
    std::multiset<int> ms;

    ms.count();

    std::map<int> m;
    std::multimap<int> mm;
}
