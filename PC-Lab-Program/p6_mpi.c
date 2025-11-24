#include <stdio.h>
#include <mpi.h>
#define SIZE 100000
int main(int argc, char *argv[])
{
  int rank, comm_sz;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  int data_send[SIZE], data_recv[SIZE];
  for (int i = 0; i < SIZE; i++)
  {
    data_send[i] = rank;
    data_recv[i] = -1;
  }
  if (rank == 0)
  {
    printf("Process 0 sending first\n");
    MPI_Send(data_send, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Recv(data_recv, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE); // 0, 0 to deadlock
  }
  else if (rank == 1)
  {
    MPI_Recv(data_recv, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, // printf here at start
             MPI_STATUS_IGNORE);
    printf("Process 1 sending first\n");
    MPI_Send(data_send, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
  printf("Process %d received first element %d\n", rank, data_recv[0]);
  MPI_Finalize();
  return 0;
}