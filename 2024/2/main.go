package main

import (
    "fmt"
    "strings"
    "os"
    "strconv"
)

func remove(slice []int, i int) []int {
    return append(slice[:i], slice[i+1:]...)
}

func parse(path string) [][]int {
    input, _ := os.ReadFile(path, )
    lines := strings.Split(strings.TrimSpace(string(input)), "\n")
	data := make([][]int, len(lines))

	for i, line := range lines {
        if line == "" {
            continue
        }

		fields := strings.Fields(line)
		data[i] = make([]int, len(fields))

		for j, field := range fields {
			data[i][j], _ = strconv.Atoi(field)
		}
	}

    return data
}

func part_a() {
    data := parse("input.txt")
    numSafe := 0

    for _, line := range data {
        lineNumSafe := 0
        if len(line) < 2 {
            continue
        }
        // increasing
        if line[1] > line[0] {
            for i := 1; i < len(line); i++ {
                diff := line[i] - line[i - 1]
                if diff > 0 && diff < 4 {
                    lineNumSafe++
                }
            }

        // decreasing
        } else if line[1] < line[0] {
            for i := 1; i < len(line); i++ {
                diff := line[i - 1] - line[i]
                if diff > 0 && diff < 4 {
                    lineNumSafe++
                }
            }
        }

        if lineNumSafe == len(line) - 1 {
            numSafe++
        }

    }

    fmt.Println(numSafe)
}

func part_b() {
    data := parse("test_input.txt")
    numSafe := 0

    for _, line := range data {
        //lineNumSafe := 0
        if len(line) < 2 {
            continue
        }
        // increasing
        if line[1] > line[0] {
            for i := 1; i < len(line); i++ {
                diff := line[i] - line[i - 1]
                if diff < 1 || diff > 3 {
                    fmt.Println(line[i - 1], line[i])
                    line = remove(line, i)
                    i--
                }
            }
        // decreasing
        } else if line[1] < line[0] {
            for i := 1; i < len(line); i++ {
                diff := line[i - 1] - line[i]
                if diff < 1 || diff > 3 {
                    fmt.Println(line[i - 1], line[i])
                    line = remove(line, i)
                    fmt.Println(line[i - 1], line[i])
                    i--
                }
            }
        }

        fmt.Println(line)
        //if lineNumSafe >= len(line) - 2 {
        //    numSafe++
        //}
    }

    fmt.Println(numSafe)
}

func main() {
    part_a()
    part_b()
}
