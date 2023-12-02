package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type Digit struct {
	label string
	value string
}

type DigitIndex struct {
	value string
	index int
}

type DigitStringIndex struct {
	value Digit
	index int
}

var zero = Digit{label: "zero", value: "0"}
var one = Digit{label: "one", value: "1"}
var two = Digit{label: "two", value: "2"}
var three = Digit{label: "three", value: "3"}
var four = Digit{label: "four", value: "4"}
var five = Digit{label: "five", value: "5"}
var six = Digit{label: "six", value: "6"}
var seven = Digit{label: "seven", value: "7"}
var eight = Digit{label: "eight", value: "8"}
var nine = Digit{label: "nine", value: "9"}

func findDigits(line string) (DigitIndex, DigitIndex) {
	len := len([]rune(line))
	index_1, index_2 := DigitIndex{value: "0", index: -1}, DigitIndex{value: "0", index: -1}
	for x, char := range line {
		if char >= 48 && char <= 57 {
			index_1.value = string(char)
			index_1.index = x
			break
		}
	}
	for x, _ := range line {
		if line[len-1-x] >= 48 && line[len-1-x] <= 57 {
			index_2.value = string(line[len-1-x])
			index_2.index = len - 1 - x
			break
		}
	}
	return index_1, index_2
}

func findStringDigits(line string) (DigitStringIndex, DigitStringIndex) {
	digitStrings := [10]Digit{zero, one, two, three, four, five, six, seven, eight, nine}
	firstIndex := DigitStringIndex{index: -1}
	lastIndex := DigitStringIndex{index: -1}
	for _, digit := range digitStrings {
		tmp1 := strings.Index(line, digit.label)
		if (tmp1 < firstIndex.index && tmp1 > -1) || firstIndex.index == -1 {
			firstIndex.value = digit
			firstIndex.index = tmp1
		}
		tmp2 := strings.LastIndex(line, digit.label)
		if tmp2 > lastIndex.index {
			lastIndex.value = digit
			lastIndex.index = tmp2
		}
	}
	return firstIndex, lastIndex

}

func extractCalValue(line string) int {
	firstDigitIndex, secondDigitIndex := findDigits(line)
	firstStringDigitIndex, secondStringDigitIndex := findStringDigits(line)

	num_1 := "0"
	if firstDigitIndex.index < firstStringDigitIndex.index && firstDigitIndex.index != -1 {
		num_1 = firstDigitIndex.value
	} else if firstStringDigitIndex.index < firstDigitIndex.index && firstStringDigitIndex.index != -1 {
		num_1 = firstStringDigitIndex.value.value
	} else if firstDigitIndex.index > firstStringDigitIndex.index {
		num_1 = firstDigitIndex.value
	} else if firstStringDigitIndex.index > firstDigitIndex.index {
		num_1 = firstStringDigitIndex.value.value
	}

	num_2 := "0"
	if secondDigitIndex.index > secondStringDigitIndex.index {
		num_2 = secondDigitIndex.value
	} else if secondStringDigitIndex.index > secondDigitIndex.index {
		num_2 = secondStringDigitIndex.value.value
	}

	number, err := strconv.Atoi(num_1 + num_2)
	if err != nil {
		panic(err)
	}
	fmt.Printf("First: %s\n", num_1)
	fmt.Printf("Last: %s\n\n", num_2)
	return number
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
		number := extractCalValue(scanner.Text())
		sum += number
	}
	fmt.Printf("%d", sum)
}
