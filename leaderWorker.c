/* leaderWorker.c
 * ... illustrates the leader-worker pattern in OpenMP
 *
 * Modified from code by Joel Adams, Calvin College, November 2009.
 * Usage: ./leaderWorker
 *
 */

#include <stdio.h>   // printf
#include <omp.h>     // OpenMP

int main() {

    int id = omp_get_thread_num();
    int numThreads = omp_get_num_threads();

    if ( id == 0 ) {  // thread with ID 0 is leader
        printf("Greetings from the leader thread, # %d of %d threads\n",
            id, numThreads);
    } else {          // threads with IDs > 0 are workers 
        printf("Greetings from a worker thread, # %d of %d threads\n",
            id, numThreads);
    }
    return 0;
}

