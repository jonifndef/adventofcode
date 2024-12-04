package main

import (
    "fmt"
    "slices"
    "strings"
    "strconv"
    "os"
    _"sort"
)

func abs(a int, b int) int {
    if a < b {
        return (b - a)
    }
    return (a - b)
}

func parse_and_sort(path string) ([]int, []int) {
    input, _ := os.ReadFile(path, )
    lines := strings.Split(string(input), "\n")

    left := make([]int, 0, 10000)
    right := make([]int, 0, 10000)

    for _, line := range lines {
        if line == "" {
            continue
        }

        line = strings.TrimSpace(line)
        pair := strings.Fields(line)

        val_1, _ := strconv.Atoi(pair[0])
        val_2, _ := strconv.Atoi(pair[1])

        left = append(left, val_1)
        right = append(right, val_2)
    }

    slices.Sort(left)
    slices.Sort(right)

    return left, right
}

func part_a() {
    left, right := parse_and_sort("input.txt")

    tot_val := 0
    for idx, _ := range left {
        tot_val += abs(left[idx], right[idx])
    }

    fmt.Println(tot_val)
}

func part_b() {
    left, right := parse_and_sort("input.txt")

    rightMap := make(map[int]int)

    for _, num := range right {
        rightMap[num]++
    }

    score := 0
    for _, num := range left {
        score += num * rightMap[num]
    }

    fmt.Println(score)
}

func main() {
    part_a()
    part_b()
}
