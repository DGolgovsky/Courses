#include <algorithm>

void sort(int *p, int *q, bool (*cmp)(int, int))
{
    for (int *m = p; m != q; ++m)
        for (int *r = m; r + 1 != q; ++r)
            // if (*(r + 1) < *r)
            if (cmp(*(r + 1), *r))
                std::swap(*r, *(r + 1));
}

bool less(int a, int b) // sort by ascend
{
    return a < b;
}

bool greater(int a, int b) // sort by descend
{
    return a > b;
}

void sort(int *p, int *q, bool asc = true)
{
    sort(p, q, asc ? &less : &greater);
}

