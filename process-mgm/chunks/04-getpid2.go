package main

import (
	"fmt"
	"os"
	"time"
)

func main() {
	for i := 0; i < 10; i++ {
		go func(i int) {
			fmt.Println(i, "my PID is: ", os.Getpid())
		}(i)
	}
	time.Sleep(time.Second * 3)
	fmt.Println("main() is finished")

	os.Exit(0)
}
