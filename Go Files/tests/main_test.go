package tests

import (
	cf "gofiles/custom-functions"
	"math/rand"
	"testing"
	"time"
) 

const (
    ROWVAL = 100
    COLVAL = 1000
)

var log = cf.InitLogger()

func testBasicArraySearch() {
    start := time.Now()
    arr := cf.Create2DArray(ROWVAL, COLVAL, 10)
    end := time.Now()

    log.Println("Generating Array Runtime: ", end.Sub(start))

    start2 := time.Now()
    for i:= 0; i < ROWVAL; i++ {
        cf.QuickSort(arr[i], 0, COLVAL-1)
        res := cf.BinarySearch(arr[i], 0, COLVAL-1, rand.Intn(10))
        if res != -1 {
            log.Println("found the target number at index ", res)
        } else {
            log.Println("target number not found for this row")
        }
    }
    end2 := time.Now()
    log.Println("Binary Search and Quicksort Runtime: ", end2.Sub(start2))

    for i:=0; i < ROWVAL; i++ {
        for j:=0; j < COLVAL; j++ {
            log.Print(arr[i][j])
            log.Print(" ")
        }
        log.Println("")
    }
}

// func TestBasicArraySearch(t *testing.T) {
//     testBasicArraySearch()
// }

// func TestFiBRecursive(t *testing.T) {
//     start := time.Now()
//     dp := make(map[int]int)
//     val := cf.FibRecursive(40, dp)
//     log.Println(val)
//     if val != 102334155 {
//         t.Errorf("got %d, want %d", val, 102334155)
//     }
//     end := time.Now()
//     log.Println("Fib Runtime: ", end.Sub(start))
// }

// func TestBlockSearch(t *testing.T) {
//     start := time.Now()
//     graph := cf.Create2DArray(ROWVAL, COLVAL, 2)
//     log.Println(cf.NumOneBlocks(graph))
//     end := time.Now()
//     log.Println("Block Search Runtime: ", end.Sub(start))
// }

func BenchmarkArraySearch(b *testing.B) {
    for i := 0; i < b.N; i++ {
        testBasicArraySearch()
    }
}


