
func NumOneBlocks(graph [][]int) int{
	rows := len(graph)
	cols := len(graph[0])

	count := 0
	for i := 0; i < rows; i++ {
		for j := 0; j < cols; j++ {
			if graph[i][j] == 1 {
				count++
				dfsHelper(i, j, graph)
			}
		}
	} 
	return count
}

func dfsHelper(i int, j int, graph [][]int) {
	if i >= len(graph) || i < 0 || j >= len(graph[0]) || j < 0 {
		return
	}
	if graph[i][j] == 0 {
		return
	}

	graph[i][j] = 0
	dfsHelper(i-1, j, graph)
	dfsHelper(i, j-1, graph)
	dfsHelper(i+1, j, graph)
	dfsHelper(i, j+1, graph)
}