#include <stdio.h>
#include <stdlib.h>
#include "../timer.h"

#define R1 10000
#define C1 1000
#define R2 1000
#define C2 10000

void matrixMult(int** m1, int** m2, int** result) {
    if(C1 != R2) {
        return; 
    }

    for(int i = 0; i < R1; i++) {
        for(int j = 0; j < C2; j++) {
            for(int k = 0; k < C1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int** create2DArray(int row, int col, int randVal) {
    int **arr = (int**)malloc(row * sizeof(int*));
    for(int i = 0; i < row; i++) {
        arr[i] = (int*)malloc(col * sizeof(int));
        for(int j = 0; j < col; j++) {
            arr[i][j] = rand() % randVal;
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

int main() {

    double start, end;
    double totalTime = 0;
    for(int i = 0; i < 10; i++) {
        int** m1 = create2DArray(R1, C1, 10);
        int** m2 = create2DArray(R2, C2, 10);
        int** result = create2DArray(R1, C2, 1);
        start = get_time();
        matrixMult(m1,m2,result);
        end = get_time();

        totalTime += end-start;
        printf("Time %.16f\n", end-start);
        free2DArray(m1);
        free2DArray(m2);
        free2DArray(result);
    }
    printf("Average total time taken: %.16f seconds", totalTime / 10);

    return 0;

}