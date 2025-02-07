#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define ROWVAL 100000
#define COLVAL  10000

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


int* createArray(int size) {
    int *arr = (int*)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

// Might be redundant, can probably juse use createArray() instead
int** create2DArray(int row, int col) {
    int **arr = (int**)malloc(row * sizeof(int*));
    for(int i = 0; i < row; i++) {
        arr[i] = (int*)malloc(col * sizeof(int));
        for(int j = 0; j < col; j++) {
            arr[i][j] = rand();
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
    for(int i = 0; i < ROWVAL; i++) {
        binarySearch(arr[i], 0, COLVAL - 1, rand());
    }
    end = clock();
    printf("Binary Search Runtime: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    free2DArray(arr);
}



int main() {
    srand(time(NULL));

    testBasicArraySearch();
    return 0;
}

