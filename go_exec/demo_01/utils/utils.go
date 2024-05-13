package utils

func GetMax[T int | float64](a, b T) T {
	if a > b {
		return a
	}
	return b
}
