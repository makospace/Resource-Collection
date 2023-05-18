package main

import (
	"fmt"
)
var c int
func isprime(n int) {
	for i := 2; i < n; i++ {
		if n % i == 0 {
			return 
		}
	}
	c ++
	fmt.Printf("%d ", c)
}

func main() {
	s := "Hello 世界"
	for i := 2; i < 100001; i++ {
		go isprime(i)
	}
	fmt.Scanln(&s)
	fmt.Println(c)
}