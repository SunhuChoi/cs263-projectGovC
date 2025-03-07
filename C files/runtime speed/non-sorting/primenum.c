#include <stdio.h>
#include <stdlib.h>
#include "../timer.h"

int isPrime(int n) {
    if (n <= 1) {
        return -1;
    }

    for(int i = 2; i <= n / 2; i++) {
        if(n % i == 0) {
            return 0;
        } 
    }

    return 1;
}

int main() {
    int n;
    double start, end;
    scanf("%d", &n);
    double totalTime = 0;
    printf("Value: %d\n", n);
    for(int i = 0; i < 10; i++) {

        start = get_time();
        int result = isPrime(n);
        end = get_time();

        totalTime += end-start;
        printf("Time %.16f\n", end-start);
        printf("Value: %d\n", result);
    }
    printf("Average total time taken: %.16f seconds", totalTime / 10);
    return 0;
}