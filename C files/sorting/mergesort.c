#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right) {

    int s1 = mid - left + 1;
    int s2 = right - mid;

    int L[s1];
    for (int i = 0; i < s1; i++)
        L[i] = arr[left + i];

    int R[s2];
    for (int j = 0; j < s2; j++)
        R[j] = arr[mid + 1 + j];

    
    int i = 0, j = 0, k = left; // merge 
    while (i < s1 && j < s2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    
    while (i < s1) { // remaining elements
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < s2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
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
    mergeSort(arr, 0, size - 1);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Merge Sort took %.6f seconds\n", time_taken);

    return 0;
}
