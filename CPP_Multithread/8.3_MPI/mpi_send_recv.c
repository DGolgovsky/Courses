int main(int argc, char **argv)
{
    char message[20];
    int i, rank, size, type = 99;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(...);
    MPI_Comm_rank(...);

    if (rank == 0) {
        strcpy(message, "Hello, World!");
        for (i = 1; i < size; ++i) {
            MPI_Send(message, 14, MPI_CHAR, i, type, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(message, 20, MPI_CHAR, 0, type, MPI_COMM_WORLD, &status);
        printf(message);
    }

    MPI_Finalize(...);

    return 0;
}
