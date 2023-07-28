package main

import (
	"fmt"
	"os/exec"
	"strconv"
	"syscall"
)

var EXIT_FAILURE = 1
var EXIT_SUCCESS = 0

func main() {
	pid := strconv.Itoa(syscall.Getpid())
	fmt.Printf("check open fd for %s PID:\n", pid)
	path := "/proc/" + pid + "/fd"
	cmd := exec.Command("ls", "-la", path)
	out, err := cmd.Output()
	if err != nil {
		fmt.Println("output '$ls -la /proc/<PID>/fd' command")
		syscall.Exit(EXIT_FAILURE)
	} else {
		fmt.Println(string(out))
	}

	syscall.Exit(EXIT_SUCCESS)
}
