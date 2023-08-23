package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func main() {
	// открываем файл для чтения
	file, err := os.OpenFile("/proc/self/maps", os.O_RDONLY, 0)
	if err != nil {
		log.Fatal("opening file:", err.Error())
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		fmt.Println(scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err.Error())
	}
}
