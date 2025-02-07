package main

import (
	"fmt"
	"log"
	"math/rand"
	"os"
	"time"
) 

const (
    ROWVAL = 100000
    COLVAL = 10000
)

var logger *log.Logger

func init() {
    if _, err := os.Stat("log"); os.IsNotExist(err) {
        os.Mkdir("log", 0750)
    }

    logFile, err := os.OpenFile(fmt.Sprintf("log/%s", time.Now().Format("2006-01-02-15-04-05")), os.O_CREATE|os.O_RDWR|os.O_APPEND, 0644)
    if err != nil {
        log.Fatal(err)
    }

    // Set up the logger
    logger = log.New(logFile, "INFO: ", log.Ldate|log.Ltime|log.Lshortfile)
}

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

func createArray(size int) []int {
    arr := make([]int, size)
    for i := 0; i < size; i++ {
        arr[i] = i
    }
    return arr
}

func create2DArray(row int, col int) [][] int {
    arr := make([][] int, row)
    for i:= 0; i < row; i++ {
        arr[i] = make([]int, col)
        for j := 0; j <col; j++ {
            arr[i][j] = rand.Intn(row*col)
        }
    }
    return arr
}

func testBasicArraySearch() {
    start := time.Now()
    arr := create2DArray(ROWVAL, COLVAL)
    end := time.Now()

    logger.Println("Generating Array Runtime: ", end.Sub(start))

    start2 := time.Now()
    for i:= 0; i < ROWVAL; i++ {
        binarySearch(arr[i], 0, COLVAL-1, rand.Intn(ROWVAL*COLVAL))
    }
    end2 := time.Now()
    logger.Println("Binary Search Runtime: ", end2.Sub(start2))
}

func main() {
    testBasicArraySearch()
}