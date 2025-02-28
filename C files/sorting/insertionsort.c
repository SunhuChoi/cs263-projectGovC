#include <stdio.h>


void insertionSort(int arr[], int n) {

    for (int i = 1; i < n; i++) { // need to have the first guy to compare against 
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) { // shifting 
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}


int main() {
    
    int arr[] = {64, 3, 25, 12, 220, 11, 0, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    

    insertionSort(arr, n);
    

    printf("final: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
