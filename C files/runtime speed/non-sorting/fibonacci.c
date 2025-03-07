#include <stdio.h>
#include <stdlib.h>
#include "../timer.h"

int fibRecursive(int n, int* dp) {
    if (n <= 1) {
        return n;
    }

    if (dp[n] != -1) {
        return dp[n];
    }
    return fibRecursive(n-2, dp) + fibRecursive(n-1, dp);

}

int fibIterative(int n) {
    if(n <= 1) {
        return n;
    }

    int a = 0, b = 1;

    for(int i = 2; i <= n; i++) {
        int temp = a;
        a = b;
        b = temp + b;
    }

    return b;
}

int* createArray(int size) {
    int *arr = (int*)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        arr[i] = -1;
    }
    return arr;
}

// int main() {
//     int n;
//     double start, end;
//     scanf("%d", &n);
//     double totalTime = 0;

//     for(int i = 0; i < 10; i++) {
//         int* dp = createArray(102334160);

//         start = get_time();
//         int result = fibRecursive(n, dp);
//         end = get_time();

//         totalTime += end-start;
//         printf("Time %.16f\n", end-start);
//         printf("%d", result);
//         free(dp);
//     }
//     printf("Average total time taken: %.16f seconds", totalTime / 10);

//     return 0;
// }

int main() {
    int n;
    double start, end;
    scanf("%d", &n);
    double totalTime = 0;

    for(int i = 0; i < 10; i++) {
        start = get_time();
        int result = fibIterative(n);
        end = get_time();

        totalTime += end-start;
        printf("Time %.16f\n", end-start);
        printf("Result: %d\n", result);
    }
    printf("Average total time taken: %.16f seconds", totalTime / 10);

    return 0;
}