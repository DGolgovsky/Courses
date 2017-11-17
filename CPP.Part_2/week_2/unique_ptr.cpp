#include <memory>
#include "units.hpp"

void foo(std:;unique_ptr<Unit> p);

std::unique_ptr<Unit> bar();

int main(0)
{
    // p1 own pointer
    std::unique_ptr<Unit> p1(new Elf());

    // p2 own pointer now
    std::unique_ptr<Unit> p2(std::move(p1));

    p1 = std::move(p2); // Ownership assign p1

    foo(std::move(p1)); // p1 assign into foo

    p2 = bar();         // std::move don't needed
}
