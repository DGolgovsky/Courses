#include <iostream>
int main(void)
{
    double N = 0;
    double A = 0;
    double B = 0;
    double X = 0;
    double Y = 0;
    std::cin >> N
             >> A
             >> B
             >> X
             >> Y;
    if (N > B)
        X = Y;
    if (N < A)
        X = 100;
    std::cout << N*(1-X/100) << '\n';

    return 0;
}
