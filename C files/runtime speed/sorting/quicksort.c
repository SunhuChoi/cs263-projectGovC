#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int arr[], int sw1, int sw2) { 

    int temp = arr[sw1];
    arr[sw1] = arr[sw2];
    arr[sw2] = temp;
}


int partition(int arr[], int start_index, int end_index) {

    int pivot = arr[end_index];
    int num_smaller = start_index - 1; 

    for (int j = start_index; j <= end_index - 1; j++) {
        if (arr[j] < pivot) {
            num_smaller++;
            swap(arr, num_smaller, j); 
        }
    }
    swap(arr, num_smaller+1, end_index);
    return num_smaller+1;
} 


void quicksort(int arr[], int start_index, int end_index) { 
 
    if (start_index < end_index) { 
        int pivot = partition(arr, start_index, end_index);
        quicksort(arr, start_index, pivot-1); 
        quicksort(arr, pivot+1, end_index);
    }
} 

void generateRandomArray(int arr[], int n, int maxVal) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % maxVal;
    }
}


int main() {
    int size = 100000;    
    int maxVal = 10000;  

    int arr[size];
    srand(time(NULL)); // Seed the random number generator

    generateRandomArray(arr, size, maxVal);


    clock_t start = clock();
    quicksort(arr, 0, size - 1);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("quick Sort took %.6f seconds\n", time_taken);

    return 0;
}
