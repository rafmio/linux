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
	var buf []byte

	if len(os.Args) != 3 || strings.Compare(os.Args[1], "--help") == 0 {
		fmt.Println("too few arguments")
		fmt.Printf("%s old-file new-file\n", os.Args[0])
		os.Exit(EXIT_FAILURE)
	}

	inputFd, err := syscall.Open(os.Args[1], syscall.O_RDONLY, 0)
	if err != nil {
		fmt.Println("opening file:", err.Error())
		os.Exit(EXIT_FAILURE)
	}
	defer syscall.Close(inputFd)

	openFlags := syscall.O_CREAT | syscall.O_WRONLY | syscall.O_TRUNC
	filePerms := syscall.S_IRUSR | syscall.S_IWUSR | syscall.S_IRGRP |
		syscall.S_IWGRP | syscall.S_IROTH | syscall.S_IWOTH // rw-rw-rw

	outputFd, err = syscall.Open(os.Args[2], openFlags, uint32(filePerms)) // VS сам привел к uint32
	if err != nil {
		fmt.Println("opening file:", err.Error())
		os.Exit(EXIT_FAILURE)
	} else {
		fmt.Printf("file opened, fd=%d\n", outputFd)
	}
	defer syscall.Close(outputFd)

	numRead, err = syscall.Read(inputFd, buf)
	if err != nil {
		fmt.Println("reading file", err.Error())
	} else {
		fmt.Printf("read %d elements\n", numRead)
	}

	numWrite, err := syscall.Write(outputFd, buf)
	if err != nil {
		fmt.Println("wirting to file", err.Error())
	} else if numWrite != numRead {
		fmt.Println("couldn't write whole buffer")
	}

	if numRead == -1 {
		fmt.Println("error read")
		os.Exit(EXIT_FAILURE)
	}

	// no need to use since using defer syscall.Close()
	// err = syscall.Close(inputFd)
	// if err != nil {
	// 	fmt.Println("closing inputFd:", err.Error())
	// 	os.Exit(EXIT_FAILURE)
	// }
	// err = syscall.Close(outputFd)
	// if err != nil {
	// 	fmt.Println("closing outputFd:", err.Error())
	// 	os.Exit(EXIT_FAILURE)
	// }

}
