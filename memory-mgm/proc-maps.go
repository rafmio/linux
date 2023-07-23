package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	directory := "/proc/"
	fileMaps := "/maps"
	fileStatus := "/status"
	pid := os.Getpid()
	pidStr := strconv.Itoa(pid)

	path := directory + pidStr + fileMaps
	contents, err := os.ReadFile(path)
	if err != nil {
		fmt.Println("reading file:", err.Error())
	}
	contentsStr := string(contents)
	fmt.Println(contentsStr)
	fmt.Println()

	path = directory + pidStr + fileStatus
	contents, err = os.ReadFile(path)
	if err != nil {
		fmt.Println("reading file:", err.Error())
	}
	contentsStr = string(contents)
	fmt.Println(contentsStr)
}