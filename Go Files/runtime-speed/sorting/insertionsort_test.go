package main

import (
	"testing"
)

func InsertionSort(arr []int) {
	leng := len(arr)

	for i := 1; i < leng; i++ {
		key := arr[i]
		j := i - 1

		for j >= 0 && arr[j] > key {
			arr[j+1] = arr[j]
			j--
		}

		arr[j+1] = key
	}
}



func BenchmarkArraySearchInsertion(b *testing.B) {
	size := 100000
	maxVal := 1000 
    for i := 0; i < b.N; i++ {
		arr := generateRandomArray(size, maxVal)
		InsertionSort(arr)
    }
}