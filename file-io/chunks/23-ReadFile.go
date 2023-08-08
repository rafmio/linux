package main

import (
	"fmt"
	"log"
	"os"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Printf("Too few arguments. Usage: '$ %s fileName'\n", os.Args[0])
		os.Exit(1)
	}
	data, err := os.ReadFile(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}

	os.Stdout.Write(data)
}
