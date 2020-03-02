#include <iostream>

void qsort(void* base, size_t num, size_t size,
           int (*compar)(void const*, void const*));

int doublecmp(void const *a, void const *b)
{
    double da = *static_cast<double const*>(a);
    double db = *static_cast<double const*>(b);
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

void sort(double *p, double *q)
{
    qsort(p, q-p, sizeof(double), &doublecmp);
}

int main()
{
    double a[] = {5.0, 4.5, 9.4, 1.3, 7.6, 2.7};
    constexpr std::size_t size = sizeof a / sizeof *a;
    sort(a, a + size);
    for (auto dd : a) {
        std::cout << dd << " ";
    }
    std::cout << std::endl;

    return 0;
}
