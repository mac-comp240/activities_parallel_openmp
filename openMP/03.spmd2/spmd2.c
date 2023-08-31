/* spmd2.c
 * ... illustrates the SPMD pattern in OpenMP,
 * 	using the commandline arguments 
 *      to control the number of threads.
 *
 * Joel Adams, Calvin College, November 2009.
 *
 * Usage: ./spmd2 [numThreads]
 *
 * TODO: Compile and run this program multiple times. Look for a "race condition",
 * which happens when different threads access shared data in a way that causes 
 * anomalous outputs. Fix the issue (look back at patternlet 2)
 */

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int id, numThreads;

    printf("\n");
    if (argc > 1) {
        omp_set_num_threads( atoi(argv[1]) );
    }

    #pragma omp parallel 
    {
        id = omp_get_thread_num();
        numThreads = omp_get_num_threads();
        printf("Hello from thread %d of %d\n", id, numThreads);
    }

    printf("\n");
    return 0;
}

