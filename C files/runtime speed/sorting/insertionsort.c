#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void insertionSort(int arr[], int n) {
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


void generateRandomArray(int arr[], int n, int maxVal) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % maxVal; // Random number between 0 and maxVal-1
    }
}


void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n = 100000;   
    int maxVal = 1000; 

    int *arr = (int *)malloc(n * sizeof(int)); 
    if (arr == NULL) {

        printf("malloc failed\n");
        return 1;
    }

    srand(time(NULL)); // Seed 
    generateRandomArray(arr, n, maxVal);


    clock_t start = clock(); 
    insertionSort(arr, n);
    clock_t end = clock();  


    double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC; 
    printf("Insertion Sort Time: %f seconds\n", timeTaken);

    free(arr); 
    return 0;
}
