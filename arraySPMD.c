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

    double t1 = omp_get_wtime();

    #pragma omp parallel for
    for (long i = 0; i < N; i++) {
        A[i] = (double)i * (double)i;
    }

    double t2 = omp_get_wtime();
    double elapsed = t2 - t1;

    printf("Done filling array! Time taken: %f\n", elapsed);
    return 0;
}

