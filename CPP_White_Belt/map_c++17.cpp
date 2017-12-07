#include <map>
#include <iostream>

int main()
{
    std::map<std::string, int> m = {{"one", 1}, {"two", 2}};
    for (const auto& [key, value] : m) {
        std::cout << "Key: " << key   << ", "
                  << "Val: " << value << "\n";
    }
    return 0;
}
