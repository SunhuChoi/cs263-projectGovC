#include <stdio.h>

void swap(int arr[], int sw1, int sw2) { 

    int temp = arr[sw1];
    arr[sw1] = arr[sw2];
    arr[sw2] = temp;
}


int partition(int arr[], int start_index, int end_index) {

    int pivot = arr[end_index];
    int num_smaller = start_index - 1; // this will later be the index of where that element should go - beginning plus how many smaller - 1 for the index

    for (int j = start_index; j <= end_index - 1; j++) {
        if (arr[j] < pivot) {
            num_smaller++;
            swap(arr, num_smaller, j); // swap that smaller element with whatever is at where it should be 
        }
    }
    swap(arr, num_smaller+1, end_index);
    return num_smaller+1; // the part that is at its correct index, need to figure everything else out still
} 


void quicksort(int arr[], int start_index, int end_index) { 
 
    if (start_index < end_index) { // if not, means that we have gone down to array size of 1
        // split the array in 2 - parition function
        int pivot = partition(arr, start_index, end_index);
        quicksort(arr, start_index, pivot-1); // new start and end index of the half array 
        quicksort(arr, pivot+1, end_index);
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

    
    quicksort(arr, 0, n);
    
    printf("final: \n"); // checking 
    for (int i = 0; i < n; i++) { 
        printf("%d ", arr[i]);
    }

    return 0;
}