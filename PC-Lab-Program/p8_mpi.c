    #include <mpi.h>
     #include <stdio.h>

    int main() {
      int rank, size;
      int send_data[4];     // Data to scatter
      int recv_data;        // Each process receives one int
      int gathered_data[4]; // Data to gather back

    MPI_Init(NULL, NULL);               // Initialize MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes

    // Initialize data at root
    if (rank == 0) {
        for (int i = 0; i < 4; i++) 
            send_data[i] = (i + 1) * 10;  // Example: 10, 20, 30, 40
        
        printf("Process 0 scatters the following data ");
        for (int i = 0; i < 4; i++) 
            printf("%d ", send_data[i]);
    }

    // Scatter data from Process 0 to all processes
   MPI_Scatter(send_data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0,              
              MPI_COMM_WORLD);

    printf(" \nProcess %d received number %d\n", rank, recv_data);
    fflush(stdout);
    // Each process doubles its received value
    recv_data *= 2;

    // Gather processed data back to Process 0
    MPI_Gather(&recv_data, 1, MPI_INT, gathered_data, 1, MPI_INT, 0, 
                MPI_COMM_WORLD);

    // Sync all process before printing
    MPI_Barrier(MPI_COMM_WORLD);
    
    // Print gathered data at Process 0
    if (rank == 0) {
    	printf("\n\nFinal gathered data: ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", gathered_data[i]);
        }
        printf("\n");
    }

    MPI_Finalize(); // Finalize MPI
    return 0;
}

/*  
Process 2 received number 30

Process 3 received number 40
Process 0 scatters the following data 10 20 30 40
Process 0 received number 10

Process 1 received number 20


Final gathered data: 20 40 60 80  */
