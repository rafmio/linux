package main

import (
	"fmt"
	"io"
	"os"
)

func main() {
	if len(os.Args) < 3 {
		fmt.Printf("Too few arguments. Usage: '%s srcFile dstFile", os.Args[0])
		os.Exit(1)
	}

	srcFile, err := os.OpenFile(os.Args[1], os.O_RDONLY, 0666)
	if err != nil {
		fmt.Println("opening file", err.Error())
		os.Exit(1)
	}
	defer srcFile.Close()

	fileInfo, _ := srcFile.Stat()
	srcFileSize := fileInfo.Size()
	fmt.Println("srcFileSize: ", srcFileSize)
	fmt.Println("srcFile mode: ", fileInfo.Mode())

	// set file position at centre:
	filePosition, err := srcFile.Seek(srcFileSize/2, io.SeekStart)
	if err != nil {
		fmt.Println("Seek():", err.Error())
		os.Exit(1)
	} else {
		fmt.Println("Current file position now is:", filePosition)
	}

	buffer := make([]byte, filePosition)
	numRead, err := srcFile.Read(buffer)
	if err != nil {
		fmt.Println("reading file:", err.Error())
		os.Exit(1)
	} else {
		fmt.Printf("%d bytes was read\n", numRead)
	}

	dstFile, err := os.OpenFile(os.Args[2], os.O_CREATE|os.O_WRONLY, 0666)
	if err != nil {
		fmt.Println("Error opening file", err.Error())
		os.Exit(1)
	}
	defer dstFile.Close()

	// write 10 bytes after start of the file
	numWrite, err := dstFile.WriteAt(buffer, 10)
	if err != nil {
		fmt.Println("Writing to a file", err.Error())
		os.Exit(1)
	} else {
		fmt.Printf("%d bytes was wrote\n", numWrite)
	}
}
