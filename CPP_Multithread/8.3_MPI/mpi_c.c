/*
 * Message Passing Interface
 * recommended MPICH
 *
 * Compile:
 * mpicc -o exe_c mpi_c.c
 *
 * Execute:
 * mpiexec -l -n 5 ./exe_c
 */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **rgv)
{
    int rank, size;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("process %d of %d\n", rank, size);

    MPI_Finalize();

    return 0;
}
