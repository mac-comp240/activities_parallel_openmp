/* parallelLoopChunksOf1.c
 * ... illustrates how to make OpenMP map threads to 
 *	parallel loop iterations in chunks of size 1
 *	(use when not accesssing memory).
 *
 * Joel Adams, Calvin College, November 2009.
 *
 * Usage: ./parallelLoopChunksOf1 [numThreads]
 *
 * TODO: Compile and run the two parallel code segments and compare the results
 * TODO: Experiment with changing static to dynamic and changing the number of iterations
 * in the schedule
 */

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    const int REPS = 16;

    printf("\n");
    if (argc > 1) {
        omp_set_num_threads( atoi(argv[1]) );
    }

    #pragma omp parallel for schedule(static,1)
    for (int i = 0; i < REPS; i++) {
        int id = omp_get_thread_num();
        printf("Thread %d performed iteration %d\n", 
                 id, i);
    }

/*
    printf("\n---\n\n");

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int numThreads = omp_get_num_threads();
        for (int i = id; i < REPS; i += numThreads) {
            printf("Thread %d performed iteration %d\n", 
                     id, i);
        }
    }
*/
    printf("\n");
    return 0;
}

