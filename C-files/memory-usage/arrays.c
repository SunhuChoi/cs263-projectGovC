#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <malloc/malloc.h>  // macOS specific header for malloc_size

#define NUM_ARRAYS 1500000  // 10,000 arrays
#define ARRAY_SIZE 1024   // 1 KB per array 

int **arrays = NULL; 
struct timeval start_time;


double getElapsedTime() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    double elapsed = (current_time.tv_sec - start_time.tv_sec) + 
                     (current_time.tv_usec - start_time.tv_usec) / 1000000.0;
    return elapsed;
}

// Function to print total allocated memory - manually finding the size using malloc lib
void printMemoryUsage() {
    size_t total_size = 0;

    // size of the main array
    if (arrays) {
        total_size += malloc_size(arrays);

        // each allocated sub-array
        for (int i = 0; i < NUM_ARRAYS; i++) {
            if (arrays[i]) {
                total_size += malloc_size(arrays[i]);
            }
        }
    }
    printf("[%.3f s] Total allocated memory: %zu bytes (%.2f MB)\n", getElapsedTime(), total_size, total_size / (1024.0 * 1024.0));
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
    gettimeofday(&start_time, NULL); // Capture the program's start time

    pthread_t monitorThread;
    pthread_create(&monitorThread, NULL, monitorMemory, NULL);

    allocateMemory();

    pthread_join(monitorThread, NULL); // Ensure monitor thread finishes

    return 0;
}
