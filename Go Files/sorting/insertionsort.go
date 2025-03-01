
func InsertionSort(arr []int) {
    leng := len(arr)

    for i := 1; i < leng; i++ {
        key := arr[i]
        j := i - 1

        for j >= 0 && arr[j] > key {
            arr[j+1] = arr[j]
            j--
        }

        arr[j+1] = key
    }
}