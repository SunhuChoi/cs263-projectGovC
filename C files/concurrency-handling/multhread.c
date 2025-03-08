#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 100000

void *print_message() {
    printf("New thread!\n");
    return 0;
}  

 
int main() {  

    pthread_t threads[NUM_THREADS]; 

    clock_t start = clock();
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, print_message, NULL);
    }

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);    
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Multi thread test took %.6f seconds\n", time_taken);

    return 0;
}
