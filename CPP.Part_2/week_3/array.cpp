#include <array>
/*
 * operator[], at,
 * back, front.
 * fill,
 * data.
 */

std::array<std::string, 3> a = {"One", "Two", "Three"};
std::cout << a.size() << std::endl;
std::cout << a[1] << std::endl;

// Runtime error
std::cout << a.at(3) << std::endl;

