/*
Credits to https://stackoverflow.com/questions/2349776/how-can-i-benchmark-c-code-easily 
for the code for QueryPerformanceCounter to be used as a high resultion timer
*/

#ifndef TIMER_H
#define TIMER_H

#include <windows.h>
double get_time()
{
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double)t.QuadPart/(double)f.QuadPart;
}

int* createArray(int size, int maxVal) {
    int *arr = (int*)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        arr[i] = rand() % maxVal;
    }
    return arr;
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

#endif