package main

import (
	"fmt"
	"os"
	"syscall"
)

func main() {
	// просто обертка для syscall.Getpid():
	// func Getpid() int { return syscall.Getpid() }
	currentPID := os.Getpid()
	fmt.Println("My PID: ", currentPID)

	// просто обертка для syscall.Getppid():
	// func Getppid() int { return syscall.Getppid() }
	parentPID := os.Getppid()
	fmt.Println("Parent's PID: ", parentPID)

	currentPID = syscall.Getpid()
	parentPID = syscall.Getppid()
	fmt.Println("PID: ", currentPID)
	fmt.Println("PPID: ", parentPID)
}
