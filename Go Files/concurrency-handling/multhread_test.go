package main

import (
	"sync"
	"testing"
) 

const numThreads = 10000000

func printMessage(threadID int, wg *sync.WaitGroup) {
	defer wg.Done() // decrease counter by 1 after function is done executing 
	var x = 0
    x +=1
}

func BenchmarkMultiThreading(b *testing.B) {
	for i := 0; i < b.N; i++ {
		var wg sync.WaitGroup

		for j := 0; j < numThreads; j++ {
			wg.Add(1)
			go printMessage(j, &wg) // Pass j as thread ID
		}

		wg.Wait() // until all goroutines are done
	}
}

// package main

// import (
// 	"sync"
// 	"testing"
// )

// const numThreads = 10000000

// func printMessage(threadID int, wg *sync.WaitGroup, counter *int, mu *sync.Mutex) {
// 	defer wg.Done() 

// 	mu.Lock()        
// 	*counter += 1    
// 	mu.Unlock()     
// }

// func BenchmarkShared(b *testing.B) {

// 	for i := 0; i < b.N; i++ {
// 		var wg sync.WaitGroup
// 		var mu sync.Mutex

// 		counter := 0 

// 		for j := 0; j < numThreads; j++ {
// 			wg.Add(1)
// 			go printMessage(j, &wg, &counter, &mu) 
// 		}

// 		wg.Wait() // Block until all goroutines are done
// 	}
// }

