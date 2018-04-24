#pragma omp parallel num_threads(4)
{
    std::cout << 1 << std::endl;
#pragma omp single
    {
        std::cout << 2 << std::endl;
    } // barrier
    // omp single nowait <- no barrier
    // omp master <- 1st thread
    std::cout << 3 << std::endl;
}

