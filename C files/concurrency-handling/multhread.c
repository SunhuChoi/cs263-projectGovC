#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 1000000
#define NUM_RUNS 1  //repeat the test

void *simpletask() { 
    int x;
    x = x+1;
    return NULL;
}   
 
void run_multithreading_test(double *runtime) {  
    pthread_t threads[NUM_THREADS]; 

    clock_t start = clock();
    
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, simpletask, NULL);
    }
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);    
    }
    
    clock_t end = clock();
    *runtime = ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    double total = 0.0;
    
    for (int i = 0; i < NUM_RUNS; i++) {


        double runtime = 0.0;

        run_multithreading_test(&runtime);
        
        total += runtime;

    }

    double average_time = total / NUM_RUNS;
    printf("\nAverage runtime over %d runs: %.6f seconds\n", NUM_RUNS, average_time);

    return 0;
}
