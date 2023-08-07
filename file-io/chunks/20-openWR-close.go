package main

import (
	"fmt"
	"os"
)

func main() {
	var fileInfo os.FileInfo
	if len(os.Args) < 3 {
		fmt.Printf("Too few arguments. Usage: '$ %s sourceFile distFile'\n", os.Args[0])
		os.Exit(1)
	}

	file, err := os.OpenFile(os.Args[1], os.O_RDONLY, 0666)
	if err != nil {
		fmt.Println("opening file:", err.Error())
		os.Exit(1)
	} else {
		fileInfo, err = file.Stat()
		if err != nil {
			fmt.Println("os.Stat():", err.Error())
			os.Exit(1)
		} else {
			fmt.Println("Name():", fileInfo.Name())
			fmt.Println("Size():", fileInfo.Size())
			fmt.Println("Mode():", fileInfo.Mode())
			fmt.Println()
		}
	}
	defer file.Close()

	fileSize := fileInfo.Size()
	buffer := make([]byte, fileSize)
	numRead, err := file.Read(buffer)
	if err != nil {
		fmt.Println("reading file:", err.Error())
	} else {
		fmt.Printf("%d bytes was read\n", numRead)
	}

	fileDist, err := os.OpenFile(os.Args[2], os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0666)
	if err != nil {
		fmt.Println("opening file:", err.Error())
		os.Exit(1)
	}
	defer fileDist.Close()

	numWrite, err := fileDist.Write(buffer)
	if err != nil {
		fmt.Println("writing to file:", err.Error())
		os.Exit(1)
	} else {
		fmt.Printf("numRead: %d, numWrite: %d\n", numRead, numWrite)
	}
	// оставить для lseek():
	// numWrite, err := fileDist.WriteAt(buffer, 0) // VS Code сам привел numRead к int64
	// if err != nil {
	// 	fmt.Println("write to file:", err.Error())
	// 	os.Exit(1)
	// } else if numRead != numWrite {
	// 	fmt.Printf("numRead %d != numWrite %d\n", numRead, numWrite)
	// }

	fmt.Println("file.Name(): ", file.Name())
}
