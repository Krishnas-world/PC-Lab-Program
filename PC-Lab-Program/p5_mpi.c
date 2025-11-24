#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    // 1. Initialize the MPI environment. This must be the first MPI call.
    // The arguments (&argc, &argv) are required for MPI setup.
    MPI_Init(&argc, &argv);
    int rank;
    // 2. Get the rank (ID) of the current process within the communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        // Code for Process 0 (The Sender)
        int number = 42;

        // MPI_Send(data_address, count, datatype, destination_rank, tag, communicator)
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Rank 0 sent number %d to Rank 1\n", number);
    }
    else if (rank == 1)
    {
        // Code for Process 1 (The Receiver)
        int received;

        // MPI_Recv(buffer_address, count, datatype, source_rank, tag, communicator, status)
        MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 1 received number %d from Rank 0\n", received);
    }

    // 3. Finalize the MPI environment. This must be the last MPI call.
    MPI_Finalize();

    return 0;
}