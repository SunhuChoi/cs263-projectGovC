#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../timer.h"
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    double time_taken = 0.0;
    double start, end;
    int size;
    scanf("%d", &size);
    for(int i = 0; i < 10; i++) {  
        int maxVal = 10000;   
    
        srand(time(NULL)); // Seed random number generator
    
        int* arr = createArray(size, maxVal);
    
        start = get_time();
        bubbleSort(arr, size);
        free(arr);
        end = get_time();

        time_taken += end-start;
        printf("Time %.16f\n", end-start);
    }
    printf("Average total time taken: %.16f seconds", time_taken / 10);
    return 0;
}
