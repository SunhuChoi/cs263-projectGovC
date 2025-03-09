#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <malloc/malloc.h> 

#define NUM_ARRAYS 1500000  
#define ARRAY_SIZE 1024   // 1 KB per array 

int **arrays = NULL; 
struct timeval start;


double getTime() {
    struct timeval curtime;
    gettimeofday(&curtime, NULL);

    double elap = (curtime.tv_sec - start.tv_sec) + 
                     (curtime.tv_usec - start.tv_usec) / 1000000.0;
    return elap;
}

// Function to print total allocated memory - manually finding the size using malloc lib
void printMemoryUsage() {
    size_t size = 0; 

    // size of the main array
    if (arrays) {
        size += malloc_size(arrays);

        // each allocated sub-array
        for (int i = 0; i < NUM_ARRAYS; i++) {
            if (arrays[i]) {
                size += malloc_size(arrays[i]);
            }
        }
    }
    printf("[%.3f s] Total allocated memory: %zu bytes (%.2f MB)\n", getTime(), size, size / (1024.0 * 1024.0));
}


void allocateMemory() { 

    usleep(500000); // time for monitor thread to start

    arrays = malloc(NUM_ARRAYS * sizeof(int *));

    for (int i = 0; i < 500000; i++) {
        arrays[i] = malloc(ARRAY_SIZE);
    }

    for (int i = 0; i < 1000000; i++) {
        arrays[i] = malloc(ARRAY_SIZE);
    }

    usleep(500000); // giving time for monitor to show 

    for (int i = 0; i < NUM_ARRAYS; i++) {
        free(arrays[i]);
    }
    free(arrays);
    arrays = NULL;

}

void *monitorMemory(void *arg) {
    (void)arg;
    for (int i = 0; i < 30; i++) { 
        printMemoryUsage();
        usleep(50000); 
    }
    return NULL;
}


int main() {
    gettimeofday(&start, NULL); 

    pthread_t monitor;
    pthread_create(&monitor, NULL, monitorMemory, NULL);

    allocateMemory();

    pthread_join(monitor, NULL); 

    return 0;
}
