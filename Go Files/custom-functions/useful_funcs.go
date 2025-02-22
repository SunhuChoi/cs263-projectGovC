package customfunctions

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

func BinarySearch(arr []int, l int, r int, x int) int {
	for l <= r {
		m := l + (r-l)/2

		if arr[m] == x {
			return m
		}

		if arr[m] < x {
			l = m + 1
		} else {
			r = m - 1
		}
	}

	return -1
}

func CreateArray(size int) []int {
	arr := make([]int, size)
	for i := 0; i < size; i++ {
		arr[i] = i
	}
	return arr
}

func Create2DArray(row int, col int, rangeVal int) [][]int {
	rand.Seed(time.Now().UnixNano()) // seed the rand

	arr := make([][]int, row)
	for i := 0; i < row; i++ {
		arr[i] = make([]int, col)
		for j := 0; j < col; j++ {
			arr[i][j] = rand.Intn(rangeVal)
		}
	}
	return arr
}

func NumOneBlocks(graph [][]int) int{
	rows := len(graph)
	cols := len(graph[0])

	count := 0
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if graph[i][j] == 1 {
				count++
				dfsHelper(i, j, graph)
			}
		}
	} 
	return count
}

func dfsHelper(i int, j int, graph [][]int) {
	if i >= len(graph) || i < 0 || j >= len(graph[0]) || j < 0 {
		return
	}
	if graph[i][j] == 0 {
		return
	}

	graph[i][j] = 0
	dfsHelper(i-1, j, graph)
	dfsHelper(i, j-1, graph)
	dfsHelper(i+1, j, graph)
	dfsHelper(i, j+1, graph)
}

func FibRecursive(n int, dp map[int]int) int{
	if n == 0 {
		return 0
	}

	if n == 1 {
		return 1
	}

	if val, exists := dp[n]; exists {
		return val
	}

	return FibRecursive(n-2, dp) + FibRecursive(n-1, dp)
}


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


func FibIterative(n int) int {
    if n <= 1 {
        return n
    }

    a, b := 0, 1
	
    for i := 2; i <= n; i++ {
        a, b = b, a+b
    }

    return b
}
