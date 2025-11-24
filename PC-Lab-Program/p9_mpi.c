    #include <mpi.h>
    #include <stdio.h>

     int main() {
        int rank, size;
        int value, sum, prod, max, min, all_sum, all_prod, all_max, all_min;

     MPI_Init(NULL, NULL);               // Initialize MPI
     MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get current process rank
     MPI_Comm_size(MPI_COMM_WORLD, &size); // Get total number of processes

      value = rank + 1; // Each process contributes its rank + 1
    
     printf(" Before Reduce--Value at Rank %d = %d\n", rank, value);
     fflush(stdout);
        MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(&value, &prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
        MPI_Reduce(&value, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
        MPI_Reduce(&value, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
      if (rank == 0) 
     {
    	printf("\nReduce:\tSUM = %d\t PROD = %d\t MAX = %d\t MIN: %d\n\n\n", sum, 
                    prod, max, min);
    	fflush(stdout);
   	    }

      MPI_Allreduce(&value, &all_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
      MPI_Allreduce(&value, &all_prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
      MPI_Allreduce(&value, &all_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
      MPI_Allreduce(&value, &all_min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
      printf("Allreduce at Rank %d - SUM = %d\t PROD = %d\t MAX = %d\t MIN = %d\n", 
               rank, all_sum, all_prod, all_max, all_min);
        fflush(stdout);
       
      MPI_Finalize(); // Finalize MPI
      return 0;
   }


/*
 Before Reduce--Value at Rank 0 = 1
 Before Reduce--Value at Rank 1 = 2
 Before Reduce--Value at Rank 3 = 4
 Before Reduce--Value at Rank 2 = 3

Reduce: SUM = 10         PROD = 24       MAX = 4         MIN: 1


Allreduce at Rank 3 - SUM = 10   PROD = 24       MAX = 4         MIN = 1
Allreduce at Rank 1 - SUM = 10   PROD = 24       MAX = 4         MIN = 1
Allreduce at Rank 0 - SUM = 10   PROD = 24       MAX = 4         MIN = 1
Allreduce at Rank 2 - SUM = 10   PROD = 24       MAX = 4         MIN = 1  */
