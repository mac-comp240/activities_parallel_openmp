/* forkJoin.c
 * ... illustrates the fork-join pattern 
 *      using OpenMP's parallel directive.
 *
 * Joel Adams, Calvin College, November 2009.
 *
 * Usage: ./forkJoin
 */
 
 // TODO: Experiment with this code with and without the pragma
 // TODO: Modify this code to see thread numbers and to change the
 // number of threads allocated

#include <stdio.h>     // printf()
#include <omp.h>       // OpenMP

int main(int argc, char** argv) {

    printf("\nBefore...\n");

    // #pragma omp parallel 
    printf("\nDuring...%d\n", omp_get_thread_num());

    printf("\n\nAfter...\n\n");

    return 0;
}

