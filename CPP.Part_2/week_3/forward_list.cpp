/*
 * Односвязный список. В любом месте контейнера вставки и удаление
 * производятся за O(1)
 */
#include <forward_list>
using std::string;

std::forward_list<string> fl = {"One", "Two"};
fl.emplace_front("Zero");
fl.push_front("Minus one");
std::cout << fl.front() << std::endl;

