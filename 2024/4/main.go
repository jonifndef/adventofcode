package main

import (
    "fmt"
    "strings"
    "os"
    //"strconv" "regexp"
)

type Direction int

const (
    none Direction = iota
    left
    topleft
    top
    topright
    right
    bottomright
    bottom
    bottomleft
)

var xmas = []string{ "X", "M", "A", "S" }

func parse(path string) [][]string {
    input, _ := os.ReadFile(path, )
    lines := strings.Split(strings.TrimSpace(string(input)), "\n")

    grid := make([][]string, len(lines))
    for i, _ := range lines {
        grid[i] = make([]string, len(lines[i]))
        for j, char := range lines[i] {
            grid[i][j] = string(char)
        }
    }

    return grid
}

func visit(x int, y int, dir Direction) {

}

func part_a() {
    grid := parse("test_input.txt")

    for i, line := range grid {
        for j, char := range line {
            if char == "X" {
                fmt.Println(char, 0, )
            }
        }
    }
}

func part_b() {

}

func main() {
    part_a()
    part_b()
}
