package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	directory := "/proc/"
	file := "/maps"
	pid := os.Getpid()
	pidStr := strconv.Itoa(pid)
	path := directory + pidStr + file
	fmt.Println("PID:", pid)

	contents, err := os.ReadFile(path)
	if err != nil {
		fmt.Println("reading file:", err.Error())
	}

	contentsStr := string(contents)

	fmt.Println(contentsStr)
}
