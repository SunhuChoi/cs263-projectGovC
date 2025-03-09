package main 

import (
	"runtime"
	"time"
	cf "gofiles/custom-functions" 
)

var startTime = time.Now()
var log = cf.InitLogger()


func allocateMemory(data [][]byte) {
	const numArrays = 500000 // million arrays 
	const arraySize = 1024    // 1 KB per array

	for i := 0; i < numArrays; i++ {

		data[i] = make([]byte, arraySize)

		if i % 2 == 0 {
			data[i][0] = byte(i % 256)
		}
	}
} 
 
// waiting bc too fast 

func allocateMemory2(data2 [][]byte) {
	const numArrays = 1000000 // million arrays 
	const arraySize = 1024    // 1 KB per array

	for i := 0; i < numArrays; i++ {

		data2[i] = make([]byte, arraySize)

		if i % 2 == 0 {
			data2[i][0] = byte(i % 256)
		}
	}
} 


func printMemStats(phase string) {
	var m runtime.MemStats
	runtime.ReadMemStats(&m)

	elapsed := time.Since(startTime).Seconds()

	log.Printf("[%.3f s] %s - Alloc: %v MB, GC Cycles: %v\n",
		elapsed, phase, m.Alloc/1024/1024, m.NumGC)
}


func startMemStatsPrinter() {
	go func() {
		for {
			printMemStats("Background Stats")
			time.Sleep(20 * time.Millisecond) // no
		}
	}()
}


func main() {
	startMemStatsPrinter()

	data := make([][]byte, 500000)
	allocateMemory(data)
	data = nil // Dereference - this interestingly does not seem to make a difference 

	data2 := make([][]byte, 2000000)
	allocateMemory2(data2)
	data2 = nil 
} 

