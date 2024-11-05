/* iterPatterns.c
 * ... illustrates the use of OpenMP's different methos for assigning
       chunks of iterations to threads
 *
 * Originally: Joel Adams, Calvin College, November 2009.
 *
 * Usage: ./iterPatterns
 *
 */

#include <stdio.h>    // printf()
#include <stdlib.h>   // atoi()
#include <omp.h>      // OpenMP

int main() {
    const int REPS = 16;

    omp_set_num_threads(4);


    #pragma omp parallel for  
    for (int i = 0; i < REPS; i++) {
        int id = omp_get_thread_num();
        printf("Thread %d performed iteration %d\n", id, i);
    }
    printf("\n");
    return 0;
}

