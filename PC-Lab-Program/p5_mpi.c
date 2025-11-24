//Write a MPI Program to demonstration of MPI_Send and MPI_Recv.
#include <stdio.h>
#include <string.h>  
#include <mpi.h>       
const int MAX_STRING = 100;
int main(void)
 {
    char greeting[MAX_STRING];
    int comm_sz;                                           // Number of processes
    int my_rank;                                       // My process rank
    MPI_Init(NULL, NULL);                    // Initialize MPI
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);   // Get total number of processes                                                          
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);   // Get this process's rank                                                   
    if (my_rank != 0)  {
        sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
        MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
else {
        printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
        for (int q = 1; q < comm_sz; q++) 
     {
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }    }
    MPI_Finalize();                // Finalize MPI
    return 0;
}


/* Greetings from process 0 of 4!
Greetings from process 1 of 4!
Greetings from process 2 of 4!
Greetings from process 3 of 4!  */