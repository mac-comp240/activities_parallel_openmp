/* spmdArray.c
 * ... illustrates SPMD
 *
 * Taken from example in PDCBeginners on Runestone
 *
 * Usage: ./spmd
 *
 */

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 2000000

int main() {
    double *A;

    A = malloc(N * sizeof(double));

    printf("Filling array...\n");

    for (long i = 0; i < N; i++) {
        A[i] = (double)i * (double)i;
    }

    printf("Done filling array!\n");

    free(A);
    return 0;
}

