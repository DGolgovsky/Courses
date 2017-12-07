#include <iostream>

int main()
{
    unsigned int start_year = 1900;
    unsigned int end_year = 2100;
    unsigned int curr_year = 1900;
    int four = 4;
    for (auto i = start_year; i < end_year; ++i) {
        if (i % 4 == 0) {
            std::cout << i << "|";
        }
        if (four == 4) {
            std::cout << curr_year;
            curr_year += four;
            four = 0;
        }
        four++;
        std::cout << '\n';
    }
    return 0;
}
