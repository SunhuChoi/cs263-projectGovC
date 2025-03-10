package main

import (
	"fmt"
	"os"
)

func main() { 

    file, err := os.Create("test1.txt") 

    defer file.Close()

    for i := 0; i < 1000; i++ {
        fmt.Fprintf(file, "Line %d\n", i)
    }
}
