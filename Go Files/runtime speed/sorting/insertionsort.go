package main

import (
	"fmt"
	"math/rand"
	"time"
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


func generateRandomArray(size int, maxVal int) []int {

	rand.Seed(time.Now().UnixNano()) // Seed 
    
	arr := make([]int, size)

	for i := 0; i < size; i++ {
		arr[i] = rand.Intn(maxVal)
	}

	return arr
}


func main() {
	size := 100000       
	maxVal := 100     
	arr := generateRandomArray(size, maxVal)

	start := time.Now()
	InsertionSort(arr)
    end := time.Now()

    fmt.Println("Insertion Sort: ", end.Sub(start))
	
}
