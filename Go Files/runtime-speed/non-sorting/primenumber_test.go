package main

import (
	"testing"
)

func isPrime(n int) int {
	if n == 0 || n == 1 {
		return -1
	}

	for i := 2; i <= n/2; i++ {
		if n%i == 0 {
			return 0
		}
	}

	return 1

}

func BenchmarkPrimeNum(b *testing.B) {
	for i := 0; i < b.N; i++ {
		isPrime(200463)
	}
}