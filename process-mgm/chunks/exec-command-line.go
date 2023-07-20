package main

import (
	"fmt"
	"io"
	"os"
	"os/exec"
	"strconv"
)

func main() {
	cmd := exec.Command("ps")
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	err := cmd.Run()
	if err != nil {
		fmt.Println("error:", err)
		return
	}

	pid := os.Getpid()
	fmt.Println("again PID: ", pid)

	fmt.Println()
	fmt.Println("opening and reading /proc/<PID>/status file")
	fmt.Println()

	pidStr := strconv.Itoa(pid)
	path := "/proc/" + pidStr + "/status"
	file, err := os.Open(path)
	if err != nil {
		fmt.Println("error opening the file: ", err)
	}
	defer file.Close()

	contents, err := io.ReadAll(file)
	if err != nil {
		fmt.Println("error reading the file: ", err)
	}

	contentsStr := string(contents)
	fmt.Println(contentsStr)

	fmt.Println()
	fmt.Println("lsof command:")
	fmt.Println()

	// err = cmd.Start()
	// if err != nil {
	// 	fmt.Println("error: ", "PID: ", pid, err)
	// 	return
	// }

	fmt.Println()
	fmt.Println("stdout: ", cmd.Stdout)
	fmt.Println("stderr: ", cmd.Stderr)
	fmt.Println(cmd)

}
