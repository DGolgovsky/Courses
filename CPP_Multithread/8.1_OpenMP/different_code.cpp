#pragma omp sections
{
#pragma omp section
    {
        // do_smt_1
    }
#pragma omp section
    {
        // do_smt_2
    }
}

// Tasks (like pthread's detach)
#pragma omp task
{
    
}
#pragma omp taskwait
