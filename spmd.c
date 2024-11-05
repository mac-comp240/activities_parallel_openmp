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
    printf("\n");

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int numThreads = omp_get_num_threads();

        printf("Hello from thread %d of %d\n", id, numThreads);
    }

    printf("\n");
    return 0;
}

