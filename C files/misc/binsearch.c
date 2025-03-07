#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWVAL 10
#define COLVAL 10

// creating 2d array, sorting each row using quicksort, binary searching through each row for a random number 


int binarySearch(int arr[], int l, int r, int x) {
    while (r >= l) {
        // Add left to (r - l) because you want to find the middle of the sub array wrt to the current left index
        int m = l + (r - l) / 2;
        if(arr[m] == x) {
            return m;
        }
        else if(arr[m] > x) {
            r = m - 1;
        }
        else {
            l = m + 1;
        }
    }
    return -1;
} 

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


// int* createArray(int size) {
//     int *arr = (int*)malloc(size * sizeof(int));
//     for(int i = 0; i < size; i++) {
//         arr[i] = i;
//     }
//     return arr;
// }


// Might be redundant, can probably juse use createArray() instead 
int** create2DArray(int row, int col) {
    int **arr = (int**)malloc(row * sizeof(int*));
    for(int i = 0; i < row; i++) {
        arr[i] = (int*)malloc(col * sizeof(int));
        for(int j = 0; j < col; j++) {
            arr[i][j] = rand() % 10;
        }
    }
    return arr;
}

void free2DArray(int **arr) {
    for(int i = 0; i < sizeof(arr); i++) {
        free(arr[i]);
    }
    free(arr);
}


void testBasicArraySearch() {
    clock_t start, end;

    // Generating 2D array of 
    start = clock();
    int **arr = create2DArray(ROWVAL, COLVAL);
    end = clock();
    printf("Generating Array Runtime: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for(int i = 0; i < ROWVAL; i++) { // performing binary search on each row of the array.. so each row of the array needs to be sorted 
        quicksort(arr[i], 0, COLVAL-1);
        int found = binarySearch(arr[i], 0, COLVAL - 1, rand() % 10); 
        if (found != -1) {
            printf("found the target number at index %d\n", found);
        }
        else{
            printf("target number not found for this row\n");
        }
        
    }
    end = clock();
    printf("Binary Search Runtime: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    // for (int i = 0; i < ROWVAL; i++) { 
    //     for (int j = 0; j < COLVAL; j++) {
    //         printf("%d ", arr[i][j]);  // Print each element with space
    //     }
    //     printf("\n");  // Print a newline after each row
    // }

    free2DArray(arr);
}


int main() {
    srand(time(NULL));

    testBasicArraySearch();
    return 0;
}

