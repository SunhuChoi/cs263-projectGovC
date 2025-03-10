package main

import (
	"testing"
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


func BenchmarkArraySearchMerge(b *testing.B) {
	size := 10
	maxVal := 100 
    for i := 0; i < b.N; i++ {
		arr := generateRandomArray(size, maxVal)
		Mergesort(arr)
    }
}