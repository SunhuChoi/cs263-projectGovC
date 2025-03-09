package main

import (
	"fmt"
	"math/rand"
	"time"
)

func Swap(arr []int, start int, end int) {

	temp := arr[start]
	arr[start] = arr[end]
	arr[end] = temp

}


func Partition(arr []int, start int, end int) int {
	
	pivot := arr[end]
	smaller := start - 1

	for i := start; i <= end - 1; i++ { 

		if arr[i] < pivot {
			smaller++
			Swap(arr, smaller, i)
		}
	}

	Swap(arr, smaller + 1, end)
	return smaller + 1
}


func QuickSort(arr []int, start int, end int) {

	if start < end {

		pivot := Partition(arr, start, end)
		QuickSort(arr, start, pivot -1)
		QuickSort(arr, pivot + 1, end)
	}

}


func generateRandomArray(size int, maxVal int) []int {

	rand.Seed(time.Now().UnixNano()) // ge
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

	fmt.Println("Unsorted array:", arr)

	start := time.Now()

	QuickSort(arr, 0, len(arr)-1)

	end := time.Now()

	fmt.Println("Sorted array:  ", arr)
	fmt.Println("QuickSort Time:", end.Sub(start))
}
