#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


void generateRandomArray(int arr[], int n, int maxVal) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % maxVal;
    }
}


void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size = 100000;      
    int maxVal = 10000;   

    int arr[size];
    srand(time(NULL)); // Seed random number generator

    generateRandomArray(arr, size, maxVal);


    clock_t start = clock();
    bubbleSort(arr, size);
    clock_t end = clock();


    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort took %.6f seconds\n", time_taken);

    return 0;
}
