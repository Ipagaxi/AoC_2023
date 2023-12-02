package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func extractCalValue(line string) int {

}

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)
	sum := 0

	for scanner.Scan() {
		sum += extractCalValue(scanner.Text())
	}
	fmt.Printf("%d", sum)
}
