package main

import "fmt"

const size = 1000000

func main() {
    arr := make([]int, 1000000)
    
    for i := 0; i < 1000000; i++ {
        arr[i] = i
    }
}
