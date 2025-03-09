package main

import "fmt"

func main() {
    
    var res int64

    for i := int64(0); i < 100000000; i++ {
        res += i
    }

    fmt.Printf("sum: %d\n", res)
}
