package main

import (
	"fmt"
	"math/rand"
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


func main() {
	size := 100000       
	maxVal := 100     
	arr := generateRandomArray(size, maxVal)

	start := time.Now()
	BubbleSort(arr)
    end := time.Now()

    fmt.Println("Insertion Sort: ", end.Sub(start))
	
}