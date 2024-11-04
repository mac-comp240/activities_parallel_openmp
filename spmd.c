/* spmd.c
 * ... illustrates the single-program-multiple-data (SPMD)
 *      pattern using two basic OpenMP commands...
 *
 * Joel Adams, Calvin College, November 2009.
 *
 * Usage: ./spmd
 *
 * TODO: Experiment with shared and unshared data in the code below
 *     * Add shared data by declaring a new int before the pragma block
 *     * Print the shared data within each thread - what happens?
 */

#include <stdio.h>
#include <omp.h>

int main() {
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

