// Visibility of values
#pragma omp parallel shared(A, B, C)
                     private(i, n)

// Loops
#pragma omp parallel for reduction(+:sum)
for (int i = 0; i < 10000000; ++i) {
    sum = sum + f(i);
}
// OR
#pragma omp parallel {
#pragma omp for
    for (...)
}

// Ordered for
#pragma omp parallel for ordered
for (int i = 0; i < size; ++i) {
    std::cout << "Cycle!" << std::endl;
#pragma omp ordered
    {
        std::cout << i << std::endl;
    }
}

// Critical section
#pragma omp parallel
{
#pragma omp critical
    {
        // run only in one thread at same time
    }
}

// Atomic
#pragma omp parallel
{
#pragma omp atomic
    n++;
}

