#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../timer.h"

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) { // Shift elements to the right
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}


void generateRandomArray(int* arr, int n, int maxVal) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % maxVal; // Random number between 0 and maxVal-1
    }
}

int main() {
    double timeTaken = 0;
    double start, end;
    int n;
    scanf("%d", &n);
    for(int i = 0; i < 10; i++) {  
        int maxVal = 1000; 

        int *arr = (int *)malloc(n * sizeof(int)); 
        if (arr == NULL) {

            printf("malloc failed\n");
            return 1;
        }

        srand(time(NULL)); // Seed 
        generateRandomArray(arr, n, maxVal);


        start = get_time();
        insertionSort(arr, n);
        free(arr); 
        end = get_time();


        timeTaken += end-start;
        printf("Time %.16f\n", end-start);
    }
    printf("Average total time taken: %.16f seconds", timeTaken / 10);
    return 0;
}
