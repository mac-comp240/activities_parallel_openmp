/* spmd.c
 * ... illustrates the single-program-multiple-data (SPMD)
 *      pattern using basic OpenMP commands...
 *
 * Originally: Joel Adams, Calvin College, November 2009.
 *
 * Usage: ./spmd
 *
 */

#include <stdio.h>
#include <omp.h>

int main() {
    int id, numThreads;
    int shared_var;
    printf("\n");

    #pragma omp parallel num_threads(4) shared(shared_var) private(id, numThreads)
    {
        id = omp_get_thread_num();
        shared_var = id;
        numThreads = omp_get_num_threads();
        printf("Hello from thread %d of %d, with shared_var=%d\n", id, numThreads, shared_var);
        printf("Another shared_var: %d\n", shared_var);
    }

    printf("\n");
    return 0;
}

