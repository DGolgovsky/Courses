/*
 * std::list - двусвязный список.
 * Можно вставлять и удалять элементы с обоих концов и в середине
 * (по итераторам). Можно итерироваться в прямом и обратном направлении.
 *
 * Документация: http://www.cplusplus.com/reference/list/list/
 *
 * std::forward_list - односвязный список (C++11).
 * Можно итерироваться только в прямом направлении,
 * но расходует меньше памяти.
 *
 * Документация:
 * http://www.cplusplus.com/reference/forward_list/forward_list/
 */

#include <list>
#include <forward_list>
#include <deque>

int main()
{
    std::list<int> l; // double-ended list

    // 0 <-[]<=>[]<=>[]<=>[]-> 0

    l.push_back();
    l.pop_back();

    l.push_front();
    l.pop_front();

    l.insert();

    l.erase(iter.from(), iter.to());
    l.remove(it);

    auto bgn = l.begin(); // cbegin, rbegin, crbegin
    auto end = l.end();

    std::forward_list<int> fl; // single-ended list

    // []->[]->[]-> 0

    std::deque<int> d; // double-ended queu

    // [ | | | | ] <-> [ | | | | ] <-> [ | | | | | ]
}
