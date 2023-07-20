package main

import (
	"fmt"
	"os"
)

func main() {
	environ := os.Environ()
	for _, env := range environ {
		fmt.Println(env)
	}

	fmt.Println()
	fmt.Println("Using Getenv():")

	path := os.Getenv("PATH")
	user := os.Getenv("USER")

	fmt.Println("$PATH:", path)
	fmt.Println("$USER:", user)
}
