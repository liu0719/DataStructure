package main

import (
	"crypto/rand"
	"fmt"
	"math/big"
)

func main() {
	result, _ := rand.Int(rand.Reader, big.NewInt(100))
	fmt.Println(result)
}
