#pragma omp parallel
{
    std::cout << 1 << std::endl;
    std::cout << 2 << std::endl;
#pragma omp barrier
    std::cout << 3 << std::endl;
}

