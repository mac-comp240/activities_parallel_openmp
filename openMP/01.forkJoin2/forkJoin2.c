/* forkJoin2.c
 * ... illustrates the fork-join pattern 
 *      using multiple OpenMP parallel directives,
 *      and changing the number of threads two ways.
 *
 * Joel Adams, Calvin College, May 2013.
 *
 * Usage: ./forkJoin2
 *
 * TODO: Predict the number of threads for each section, and experiment
 * TODO: to check your predictions
 */

#include <stdio.h>    // printf()
#include <omp.h>      // OpenMP

int main(int argc, char** argv) {

    printf("\nBeginning\n");

    #pragma omp parallel 
    printf("\nPart I");

    printf("\n\nBetween I and II...\n");

    omp_set_num_threads(3);

    #pragma omp parallel 
    printf("\nPart II...");

    printf("\n\nBetween II and III...\n");

    #pragma omp parallel num_threads(5)
    printf("\nPart III...");
/*
    printf("\n\nBetween III and IV...\n");

    #pragma omp parallel 
    printf("\nPart IV...");
*/
    printf("\n\nEnd\n\n");

    return 0;
}

