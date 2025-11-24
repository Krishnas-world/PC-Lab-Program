   Program6
   Write a MPI program to demonstration of deadlock using point to point communication and avoidance of deadlock by altering the call        
   sequence.

   -----------------------------
   Deadlock
    -----------------------------

     #include <stdio.h>
     #include <mpi.h>

     #define SIZE 100000  // Large enough to demonstrate potential deadlock 
                           //(define SIZE 1 No hang)

   int main(int argc, char *argv[]) {
     int rank, comm_sz;
     MPI_Init(&argc, &argv);
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    int data_send[SIZE], data_recv[SIZE];
    for (int i = 0; i < SIZE; i++) {
        data_send[i] = rank;
        data_recv[i] = -1;
    }

      if (rank == 0) {
        printf("Process 0 sending first\n");
        MPI_Send(data_send, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(data_recv, SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (rank == 1) {
        
        printf("Process 1 sending first\n");
        MPI_Send(data_send, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(data_recv, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    printf("Process %d received first element %d\n", rank, data_recv[0]);

    MPI_Finalize();
    return 0;
}


    //During execution, set np = 2.
   //It will then display two statements and hang.
  //Press Ctrl+C and hit Enter to exit.
  //After else if 

        MPI_Recv(data_recv, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("Process 1 sending first\n");
        MPI_Send(data_send, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);    



   //To avoid deadlock in the program, 
  //the MPI_Recv function in the else part was moved to the first statement.
  //Then you will get the correct output, and the program will terminate properly.


/* out put if SIZE =1 (no changes in code)
Process 0 sending first
Process 1 sending first
Process 1 received first element 0
Process 0 received first element 1*/

/* SIZE large
Process 0 sending first
Process 1 sending first
-


Press Ctrl+C and hit Enter to exit

modify the else part in code
Process 0 sending first
Process 1 sending first
Process 0 received first element 1
Process 1 received first element 0  */




