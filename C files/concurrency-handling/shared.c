#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 1000000
#define NUM_RUNS 1 

int count = 0;  
pthread_mutex_t mutex; 

void *thread_function(void *arg) {

    pthread_mutex_lock(&mutex);

    count++;  
    
    pthread_mutex_unlock(&mutex);  
    
    // printf("New thread! count: %d\n", count);

    return NULL;
}  

void run_multithreading_test(double *runtime) {
    pthread_t threads[NUM_THREADS]; 
    count = 0;  // reset 

    clock_t start = clock();
    
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);    
    }
    
    clock_t end = clock();
    *runtime = ((double)(end - start)) / CLOCKS_PER_SEC;
}


int main() {
    double total = 0.0;

    pthread_mutex_init(&mutex, NULL);  
    
    for (int i = 0; i < NUM_RUNS; i++) {

        double runtime = 0.0;

        run_multithreading_test(&runtime);

        total += runtime;
    }

    double avgtime = total / NUM_RUNS;
    printf("\nAverage runtime over %d runs: %.6f seconds\n", NUM_RUNS, avgtime);

    pthread_mutex_destroy(&mutex);  

    return 0;
}
