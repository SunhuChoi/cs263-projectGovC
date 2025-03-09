
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


func FibRecursive(n int, mp map[int]int) int{
	
	if n == 0 {
		return 0
	}

	if n == 1 {
		return 1
	}

	if val, exists := mp[n]; exists {
		return val
	}

	return FibRecursive(n-2, mp) + FibRecursive(n-1, mp)
}