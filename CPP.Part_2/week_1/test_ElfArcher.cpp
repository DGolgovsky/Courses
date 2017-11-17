#include "ElfArcher.h"
#include <vector>

int main()
{
    std::vector<ElfArcher> players;
    for (size_t i = 0; i < 10; ++i) {
        players.push_back(ElfArcher(i));
    }

    for(auto const &it : players) {
        std::cout << it.id() << ",";
        //std::cout << static_cast<const Unit*>(&it)->id << ",";
    }

    std::cout << std::endl;

    return 0;
}

