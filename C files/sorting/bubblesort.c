#include <stdio.h>

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


int main() {

    int arr[] = {64, 3, 25, 12, 220, 11, 0, 9}; // just a test one
    int n = sizeof(arr) / sizeof(arr[0]); // rhuh

    // for (int i = 0; i < n; i++) {
    //     printf("%d ", arr[i]);
    // }

    printf("Unsorted: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    
    bubbleSort(arr, n);
    
    printf("final: \n"); // checking 
    for (int i = 0; i < n; i++) { 
        printf("%d ", arr[i]);
    }

    return 0;
}
