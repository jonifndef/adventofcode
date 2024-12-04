package main

import (
    "fmt"
    "strings"
    "os"
    "strconv"
    "regexp"
)

func remove(slice []int, i int) []int {
    return append(slice[:i], slice[i+1:]...)
}

func parse(path string) []string {
    input, _ := os.ReadFile(path, )
    lines := strings.Split(strings.TrimSpace(string(input)), "\n")

    return lines
}

func part_a() {
    lines := parse("input.txt")
    sum := 0
	for _, line := range lines {
        if line == "" {
            continue
        }

        r := regexp.MustCompile("mul\\((\\d{1,3},\\d{1,3})\\)")
        match := r.FindAllStringSubmatch(line, -1)

        for i, _ := range match {
            pair := strings.Split(match[i][1],`,`)

            first, _ := strconv.Atoi(pair[0])
            second, _ := strconv.Atoi(pair[1])
            sum += (first * second)
        }

	}

    fmt.Println(sum)
}

func part_b() {

}

func main() {
    part_a()
    part_b()
}
