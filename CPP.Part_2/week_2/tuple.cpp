#include <iostream>
#include <tuple>

std::tuple<std::string, int, int> getUnitInfo(int id)
{
    if (id == 0) return std::make_tuple("Elf",   60, 9);
    if (id == 1) return std::make_tuple("Dwarf", 60, 6);
    if (id == 2) return std::make_tuple("Orc",   60, 3);
    // ...
    return std::make_tuple("", 0, 0);

}

int main()
{
    auto ui0 = getUnitInfo(0);
    std::cout << "race: " << std::get<0>(ui0) << ", "
              << "hp: "   << std::get<1>(ui0) << ", "
              << "iq: "   << std::get<2>(ui0) << '\n';

    // Analogue
    std::string race1; int hp1; int iq1;
    std::tie(race1, hp1, iq1) = getUnitInfo(1);
    std::cout << "race: " << race1 << ", "
              << "hp: "   << hp1   << ", "
              << "iq: "   << iq1   << '\n';

    return 0;
}
