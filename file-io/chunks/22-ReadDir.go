package main

import (
	"fmt"
	"os"
)

func main() {
	if len(os.Args) < 3 {
		fmt.Printf("Too few arguments. Usage: '%s fileName dirName'\n", os.Args[0])
		os.Exit(1)
	}

	file, err := os.OpenFile(os.Args[1], os.O_RDONLY, 0666)
	if err != nil {
		fmt.Println("opening file", err.Error())
		os.Exit(1)
	}
	defer file.Close()

	// Пока так и не понял, как адекватно прочитать содержание директории
	dir, err := os.ReadDir(os.Args[2])
	if err != nil {
		fmt.Println("opening dir")
		os.Exit(1)
	}

	for i, entry := range dir {
		fmt.Println(i, entry)
	}

	os.Exit(0)
}
