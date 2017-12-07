#include <iostream>

int main(void)
{
    int A = 0;
    int B = 0;
    std::cin >> A >> B;
    if (!B) {
        std::cout<<"Impossible\n";
        return -1;
    }

    std::cout << A/B << '\n';

    return 0;
}
