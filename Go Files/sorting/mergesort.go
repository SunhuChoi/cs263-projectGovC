package main

import (
	"fmt" // for printing 
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

func main() {
	arr := []int{49, 57, 60, 3, 22, 12, 10, 3, 5}
	fmt.Println("Unsorted array:", arr)

	sortedArr := Mergesort(arr)
	fmt.Println("Sorted array:", sortedArr)
}