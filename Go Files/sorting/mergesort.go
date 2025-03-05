package main

import (
	"fmt"
	"math/rand"
	"time"
)

func Mergesort(arr []int) []int {
	if len(arr) <= 1 {
		return arr // base case 
	}

	mid := len(arr) /2 
	left := arr[:mid]
	right := arr[mid:]

	left = Mergesort(left)
	right = Mergesort(right)

	return merge(left, right)
}

func merge(left []int, right []int) []int {

	res := make([]int, 0, len(left)+len(right)) // inbuilt function to make an integer slice that is big enough - starts w 0 elems
	l := 0
	r := 0

	for l < len(left) && r < len(right) {
		if left[l] < right[r] {
			res = append(res, left[l])
			l++
		} else {
			res = append(res, right[r])
			r++
		}
	}

	res = append(res, left[l:]...) // syntax for unpacking the rest of the slice and adding the elements individually
	res = append(res, right[r:]...)

	return res
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
	sortedArr := Mergesort(arr)
	end := time.Now()

	fmt.Println(sortedArr)

	fmt.Println("Merge Sort: ", end.Sub(start))
}