package main

import (
	"math/rand"
	"testing"
)

const (
    ROWVAL = 10000
    COLVAL = 1000
)

func matrixMult(m1 [][]int, m2 [][]int, result [][]int) {
	R1, C1, R2, C2 := len(m1), len(m1[0]), len(m2), len(m2[0])

	if C1 != R2 {
		return
	}

	for i := 0; i < R1; i++ {
		for j := 0; j < C2; j++ {
			result[i][j] = 0
			for k := 0; k < C1; k++ {
				result[i][j] += m1[i][k] * m2[k][j]
			}
		}
	}
}

func create2DArray(row int, col int) [][]int {
	arr := make([][]int, row)
	for i := 0; i < row; i++ {
		arr[i] = make([]int, col)
		for j := 0; j < col; j++ {
			arr[i][j] = rand.Intn(row * col)
		}
	}
	return arr
}

func BenchmarkMatrixMult(b *testing.B) {
	m1 := create2DArray(ROWVAL, COLVAL)
	m2 := create2DArray(COLVAL, ROWVAL)

	result := make([][]int, ROWVAL)
	for i := 0; i < ROWVAL; i++ {
		result[i] = make([]int, ROWVAL)
	}
	for i := 0; i < b.N; i++ {

		matrixMult(m1,m2, result)
	}
}