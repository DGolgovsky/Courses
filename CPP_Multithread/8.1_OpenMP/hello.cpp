#include <iostream>

int main(int argc, char **argv)
{
    // 1. num_threads(4)
#pragma omp parallel num_threads(4)
{
    std::cout << "Hello, World!" << std::endl;
}

    // 2. omp_set_num_threads(4)
    // 3. export OMP_NUM_THREADS=4;

    return 0;
}
