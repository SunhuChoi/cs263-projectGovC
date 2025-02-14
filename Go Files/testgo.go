package main

import (
     cf "gofiles/custom-functions"
    "math/rand"
    "time"
    "fmt"
) 

const (
    ROWVAL = 10
    COLVAL = 10
)

var log = cf.InitLogger()

func binarySearch(arr []int, l int, r int, x int) int {
    for l <= r {
        m := l + (r - l) / 2

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

// func createArray(size int) []int { 
//     arr := make([]int, size)
//     for i := 0; i < size; i++ {
//         arr[i] = i
//     }
//     return arr
// }

func create2DArray(row int, col int) [][] int {
    rand.Seed(time.Now().UnixNano()) // seed the rand

    arr := make([][] int, row)
    for i:= 0; i < row; i++ {
        arr[i] = make([]int, col)
        for j := 0; j <col; j++ {
            arr[i][j] = rand.Intn(10)
        }
    }
    return arr
}

func testBasicArraySearch() {
    start := time.Now()
    arr := create2DArray(ROWVAL, COLVAL)
    end := time.Now()

    log.Println("Generating Array Runtime: ", end.Sub(start))

    start2 := time.Now()
    for i:= 0; i < ROWVAL; i++ {
        cf.QuickSort(arr[i], 0, COLVAL-1)
        res := binarySearch(arr[i], 0, COLVAL-1, rand.Intn(10))
        if res != -1 {
            fmt.Print("found the target number at index ", res, "\n")
        } else {
            fmt.Print("target number not found for this row \n")
        }
    }
    end2 := time.Now()
    log.Println("Binary Search and Quicksort Runtime: ", end2.Sub(start2))

    for i:=0; i < ROWVAL; i++ {
        for j:=0; j < COLVAL; j++ {
            fmt.Print(arr[i][j])
            fmt.Print(" ")
        }
        fmt.Println("")
    }

}

func main() {
    testBasicArraySearch()
    ohayo()
}
