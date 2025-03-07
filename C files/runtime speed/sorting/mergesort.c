#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../timer.h"

void merge(int* arr, int left, int mid, int right) {

    int s1 = mid - left + 1;
    int s2 = right - mid;

    int* L = (int*)malloc(s1 * sizeof(int));
    
    for (int i = 0; i < s1; i++)
        L[i] = arr[left + i];

    int* R = (int*)malloc(s2 * sizeof(int));
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
    free(L);
    free(R);
}

void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    double time_taken = 0;
    double start, end;
    int size;
    scanf("%d", &size);
    for(int i = 0; i < 10; i++) {   
        int maxVal = 10000;  

        int* arr = createArray(size, maxVal);
        srand(time(NULL)); // Seed the random number generator

        start = get_time();
        mergeSort(arr, 0, size - 1);
        free(arr);
        end = get_time();

        time_taken += end-start;
        printf("Time %.16f\n", end-start);
    }
    printf("Average total time taken: %.16f seconds", time_taken / 10);
    return 0;
}
