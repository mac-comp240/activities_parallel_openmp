/* reduction.c
 * ... illustrates the OpenMP parallel-for loop's reduction clause
 *
 * Originally: Joel Adams, Calvin College, November 2009.
 *
 * Usage: ./reduction 
 *
 */

#include <stdio.h>   // printf
#include <omp.h>     // OpenMP
#include <stdlib.h>  // rand

void initialize(int* a, int n);
int sequentialSum(int* a, int n);
int parallelSum(int* a, int n);

#define SIZE 1000000

int main() {
    int *array;

    array = malloc(SIZE * sizeof(int));
    if (array == NULL) {
        printf("Malloc failed!\n");
        exit(1);
    }

    initialize(array, SIZE);
    
    int sum1 = sequentialSum(array, SIZE);
    int sum2 = parallelSum(array, SIZE);
    printf("\nSeq. sum: \t%d\n", sum1);
    printf("Par. sum: \t%d\n\n", sum2);

    return 0;
} 

/* fill array with random values */
void initialize(int* a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        a[i] = rand() % 1000;
    }
}

/* sum the array sequentially */
int sequentialSum(int* a, int n) {
    int sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

/* sum the array using multiple threads */
int parallelSum(int* a, int n) {
    int sum = 0;
    int i;

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

