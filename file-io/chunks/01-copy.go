package main

import (
	"fmt"
	"os"
	"strings"
	"syscall"
)

var BUF_SIZE int = 1024
var EXIT_FAILURE int = 1

func main() {
	var inputFd, outputFd int
	// var openFlags int
	// var filePerms uint32
	var numRead int
	// var buf [BUF_SIZE]byte - не сработало!
	buf := make([]byte, 2048)

	if len(os.Args) != 3 || strings.Compare(os.Args[1], "--help") == 0 {
		fmt.Println("too few arguments")
		fmt.Printf("%s old-file new-file\n", os.Args[0])
		os.Exit(EXIT_FAILURE)
	}

	inputFd, err := syscall.Open(os.Args[1], syscall.O_RDONLY, 0)
	if err != nil {
		fmt.Println("opening file:", err.Error())
		os.Exit(EXIT_FAILURE) // syscall.Exit(EXIT_FAILURE)
	}
	defer syscall.Close(inputFd)

	openFlags := syscall.O_CREAT | syscall.O_WRONLY | syscall.O_TRUNC
	filePerms := syscall.S_IRUSR | syscall.S_IWUSR | syscall.S_IRGRP |
		syscall.S_IWGRP | syscall.S_IROTH | syscall.S_IWOTH // rw-rw-rw

	// VS Code постоянно сам приводит filePerms к uint32
	outputFd, err = syscall.Open(os.Args[2], openFlags, uint32(filePerms)) // VS сам привел к uint32
	if err != nil {
		fmt.Println("opening file:", err.Error())
		os.Exit(EXIT_FAILURE)
	} else {
		fmt.Printf("file opened, fd=%d\n", outputFd)
	}
	defer syscall.Close(outputFd)
	
// --------------READ---------------------------------------------------
	numRead, err = syscall.Read(inputFd, buf)
	if err != nil {
		fmt.Println("reading file", err.Error())
	} else {
		fmt.Printf("read %d elements\n", numRead)
	}
// --------------WRITE---------------------------------------------------
	numWrite, err := syscall.Write(outputFd, buf)
	if err != nil {
		fmt.Println("wirting to file", err.Error())
	} else if numWrite != numRead {
		fmt.Println("couldn't write whole buffer")
	}
}
		// For check opened fd:
		// fmt.Println("opened fd: ", inputFd)
		// pid := strconv.Itoa(syscall.Getpid())
		// fmt.Printf("check open fd for %s PID:\n", pid)
		// path := "/proc/" + pid + "/fd"
		// cmd := exec.Command("ls", "-la", path)
		// out, err := cmd.Output()
		// if err != nil {
		// 	fmt.Println("output '$ls -la /proc/<PID>/fd' command")
		// 	syscall.Exit(EXIT_FAILURE)
		// } else {
		// 	fmt.Println(string(out))
		// }
