/* arraySPMD.c
 * ... illustrates SPMD operating on an array
 *
 * Author: Susan Fox (Based on examples from PCB and other assignments)
 * Usage: ./arraySPMD
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

