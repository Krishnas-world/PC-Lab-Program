  #include <stdio.h>
  #include <omp.h>
  int main() {
    int n;
    printf("Enter number of iterations: ");
    scanf("%d", &n);

    #pragma omp parallel for schedule(static, 2)
    for (int i = 0; i < n; i++) {
        int tid = omp_get_thread_num();
        printf("Thread %d is executing iteration %d\n", tid, i);
    }
    return 0;
  }
/* Enter number of iterations: 4
Thread 1 is executing iteration 2
Thread 1 is executing iteration 3
Thread 0 is executing iteration 0
Thread 0 is executing iteration 1  */