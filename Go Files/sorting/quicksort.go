import (
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
	num_smaller := start - 1

	for i := start; i <= end-1; i++ {
		if arr[i] < pivot {
			num_smaller++
			Swap(arr, num_smaller, i)
		}
	}
	Swap(arr, num_smaller+1, end)
	return num_smaller + 1
}

func QuickSort(arr []int, start int, end int) {

	if start < end {
		pivot := Partition(arr, start, end)
		QuickSort(arr, start, pivot-1)
		QuickSort(arr, pivot+1, end)
	}
}