package main

import "fmt"

func main() {
    
    var result int64

    for i := int64(0); i < 100000000; i++ {
        result += i
    }

    fmt.Printf("Sum: %d\n", result)
}
