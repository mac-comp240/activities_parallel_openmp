/* forkJoin.c
 * ... illustrates the fork-join pattern using OpenMP's parallel directive.
 *
 * Originally by: Joel Adams, Calvin College, November 2009.
 *
 * Usage: ./forkJoin
 */
 
#include <stdio.h>     // printf
#include <omp.h>       // OpenMP

int main(int argc, char** argv) {

    printf("\nBefore...\n\n");

    //#pragma omp parallel
    { 
    printf("\nDuring...\n");
    }

    printf("\n\nAfter...\n\n");

    return 0;
}

