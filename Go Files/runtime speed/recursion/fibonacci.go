
func FibIterative(n int) int {
    if n <= 1 {
        return n
    }

    a, b := 0, 1
	
    for i := 2; i <= n; i++ {
        a, b = b, a+b
    }

    return b
}


func FibRecursive(n int, dp map[int]int) int{
	if n == 0 {
		return 0
	}

	if n == 1 {
		return 1
	}

	if val, exists := dp[n]; exists {
		return val
	}

	return FibRecursive(n-2, dp) + FibRecursive(n-1, dp)
}