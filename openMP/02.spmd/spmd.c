/* spmd.c
 * ... illustrates the single-program-multiple-data (SPMD)
 *      pattern using two basic OpenMP commands...
 *
 * Joel Adams, Calvin College, November 2009.
 *
 * Usage: ./spmd
 *
 * TODO: Experiment with shared and unshared data in the code below
 */

#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {
    printf("\n");
    int shared_var = 0;

    // #pragma omp parallel // num_threads(4) /* Uncomment this line in stages to see the effects! */
    {
        int id = omp_get_thread_num();
        int numThreads = omp_get_num_threads();
        shared_var = id;
        printf("Hello from thread %d of %d with shared value %d\n", id, numThreads, shared_var);
        printf("Shared value: %d\n", shared_var);
        if (shared_var != id) {
            printf("WRONG!\n");
        }
    }

    printf("\n");
    return 0;
}

