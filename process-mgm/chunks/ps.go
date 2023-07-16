package main

import (
    "fmt"
    "os/exec"
)

func main() {
    cmd := exec.Command("ps")
    cmd.Args = []string{"-A"} // показывает все процессы

    stdout, err := cmd.Output()
    if err != nil {
        fmt.Println("Error executing command:", err)
    } else {
        fmt.Printf("%s\n", stdout)
    }
}