package main

import (
	"math/rand"
	"testing"
	"time"
)

func BubbleSort(arr []int) {
    leng := len(arr)

    for i := 0; i < leng-1; i++ {

        for j := 0; j < leng-i-1; j++ {
            if arr[j] > arr[j+1] {
                arr[j], arr[j+1] = arr[j+1], arr[j]
            }
        }

    }
}

func generateRandomArray(size int, maxVal int) []int {

	rand.Seed(time.Now().UnixNano()) // Seed 
    
	arr := make([]int, size)

	for i := 0; i < size; i++ {
		arr[i] = rand.Intn(maxVal)
	}

	return arr
}

func BenchmarkArraySearchBubble(b *testing.B) {
	size := 10       
	maxVal := 100 
    for i := 0; i < b.N; i++ {
        arr := generateRandomArray(size, maxVal)
		BubbleSort(arr)
    }
}