// Write a OpenMP program to find the prime numbers from 1 to n 
// employing parallel for directive. Record both serial and parallel 
// execution times.
// Program-4

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int is_prime(int x) {
    if (x < 2) return 0;
    for (int d = 2; d * d <= x; d++)
        if (x % d == 0) return 0;
    return 1;
}

int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        printf("Usage: %s <n> <threads>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    int threads = atoi(argv[2]);
    omp_set_num_threads(threads);

    int count;
    double t0, t1;

    // Serial
    count = 0;
    t0 = omp_get_wtime();
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) count++;
    }
    t1 = omp_get_wtime();
    printf("Serial: %d primes, %f sec\n", count, t1 - t0);

    // Parallel
    count = 0;
    t0 = omp_get_wtime();
    #pragma omp parallel for reduction(+:count)
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) count++;
    }
    t1 = omp_get_wtime();
    printf("Parallel (%d threads): %d primes, %f sec\n", threads, count, t1 - t0);

    return 0;
}

/* narayan@LAPTOP-14N9T3JB:/mnt/c/WINDOWS/system32$ ./a.out 100000 4
Serial: 9592 primes, 0.014405 sec
Parallel (4 threads): 9592 primes, 0.009730 sec */



