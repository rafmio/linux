package main

import (
	"fmt"
	"os"
	"time"
)

func main() {
	hostname, _ := os.Hostname()
	fmt.Println("hostname: ", hostname)
	wd, _ := os.Getwd()
	fmt.Println("Getwd():", wd)
	fmt.Println("------")

	os.Setenv("SERVER", "merver")
	os.Setenv("PORT", "mort")
	fmt.Println(os.Getenv("SERVER"))
	fmt.Println(os.Getenv("PORT"))
	userHomeDir, _ := os.UserHomeDir()
	fmt.Println("------")
	fmt.Println("user home dir:", userHomeDir)
	fmt.Println("------")
	os.WriteFile("/dev/fd/1", []byte("Hello-mello, tosy-bosy\n"), 0666)
	fmt.Println("------")
	files, _ := os.ReadDir("/proc/1/attr")
	for _, file := range files {
		fmt.Println(file.Name())
	}

	fmt.Println("------")
	process, _ := os.StartProcess("./04-getpid2", nil, nil)
	if process.Pid == 0 {
		time.Sleep(time.Second * 1)
		fmt.Println("My PID: ", os.Getpid())
	} else {
		fmt.Println("My PID: ", os.Getpid())
	}
}
