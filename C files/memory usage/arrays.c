#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>
#include <pthread.h>

#define NUM_ARRAYS 1000000 // 1 million arrays
#define ARRAY_SIZE 1024     // 1 KB per array

void allocateMemory() {
    unsigned char **data = malloc(NUM_ARRAYS * sizeof(unsigned char *));
    if (!data) {
        perror("Memory allocation failed");
        exit(1);
    }

    for (int i = 0; i < NUM_ARRAYS; i++) {
        data[i] = malloc(ARRAY_SIZE);
        if (!data[i]) {
            perror("Memory allocation failed");
            exit(1);
        }

        // Simulate memory usage
        memset(data[i], i % 256, ARRAY_SIZE);

        if (i % 100000 == 0) {
            printf("Allocated %d MB\n", (i * ARRAY_SIZE) / (1024 * 1024));
        }
    }

    // Free memory (to contrast manual vs. automatic GC in Go)
    for (int i = 0; i < NUM_ARRAYS; i++) {
        free(data[i]);
    }
    free(data);
}

void printMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Memory Usage: %ld MB\n", usage.ru_maxrss / 1024);
}

void *monitorMemory(void *arg) {
    (void)arg;
    while (1) {
        printMemoryUsage();
        usleep(500000); // Sleep 500ms
    }
    return NULL;
}

int main() {
    pthread_t monitorThread;
    pthread_create(&monitorThread, NULL, monitorMemory, NULL);

    allocateMemory();

    sleep(3); // Give time for observation

    return 0;
}
