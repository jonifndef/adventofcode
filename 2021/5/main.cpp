#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <unistd.h>
#include <unordered_map>
#include <chrono>

#include <ctype.h>
#include <string.h>

struct Coord
{
    Coord(int x, int y) : x(x), y(y)
    {}

    bool operator==(const Coord& other) const
    {
        return (this->x == other.x && this->y == other.y);
    }

    int x = 0;
    int y = 0;
};

template<>
struct std::hash<Coord>
{
    std::size_t operator()(const Coord& other) const
    {
        return (std::hash<int>()(other.x) ^
                std::hash<int>()(other.y) << 1);
    }
};

struct Input
{
    Input(int x1, int y1, int x2, int y2) :
          line(std::make_pair<Coord, Coord>(Coord(x1, y1), Coord(x2, y2)))
    {}

    std::pair<Coord, Coord> line;
};

std::unordered_map<std::string, std::string> parseArgs(int argc, char* argv[])
{
    std::unordered_map<std::string, std::string> arguments;

    const static std::string usage =
        "Usage: aoc -i inputfile -p part [-s solution_number]\n"
        "\t-i inputfile: specify inputfile. Required\n"
        "\t-p part: specify which part to solve. Required\n"
        "\t-s solution: specify solution number if multiple are available\n"
        "\t-h: prints this message";

    bool invalid = false;
    int arg;
    while ((arg = getopt(argc, argv, "i:psh")) != -1)
    {
        switch(arg)
        {
            case 'i':
                arguments["input"] = std::string(optarg);
                break;
            case 'p':
                {
                    auto part = optarg;

                    if (!isdigit(std::stoi(part)))
                    {
                        std::cout << "Option -" << arg << " requires an integer argument" << std::endl;
                        break;
                    }

                    arguments["part"] = std::string(part);
                }
                break;
            case 's':
                arguments["solution"] = std::string(optarg);
                break;
            case 'h':
                std::cout << usage << std::endl;
                invalid = true;
                break;
            case '?':
                if (optopt == 'i')
                {
                    std::cout << "Option -" << optopt << " requires an argument" << std::endl;
                }
                if (optopt == 'p')
                {
                    std::cout << "Option -" << optopt << " requires an integer argument" << std::endl;
                }
                else
                {
                    invalid = true;
                    std::cout << usage << std::endl;
                }
                break;
            default:
                break;
        }
    }

    //if (!invalid &&
    //    (!arguments.contains("input") ||
    //     !arguments.contains("part")))
    //{
    //    std::cout << usage << std::endl;
    //    arguments.clear();
    //}
    //invalid = false;
    (void)invalid;

    return arguments;
}

std::vector<std::string> splitString(const std::string& inputString, const char* deliminator)
{
    std::vector<std::string> subStrings;

    const int len = strlen(deliminator);
    char *buff = (char*)calloc(len, sizeof(char));

    const char* token = inputString.c_str();
    bool tokenStarted = false;
    std::string subString;
    while (*token != '\0')
    {
        strncpy(buff, token, len);

        if (strncmp(buff, deliminator, len))
        {
            tokenStarted = true;
            subString += *token;
        }
        else
        {
            if (tokenStarted)
            {
                subStrings.push_back(subString);
                tokenStarted = false;
                subString.clear();
            }
            token += (len - 1);
        }
        token++;
    }

    if (tokenStarted && !subString.empty())
    {
        subStrings.push_back(subString);
    }

    free(buff);
    return subStrings;
}

Input formatInput(const std::vector<std::string>& subStrings)
{
    Input input(0,0,0,0);

    if (subStrings.size() != 2)
    {
        std::cout << "Error when parsing!" << std::endl;
        return input;
    }

    const auto coordsFirst = splitString(subStrings[0], ",");
    const auto coordsSecond = splitString(subStrings[1], ",");

    input.line.first.x = std::stoi(coordsFirst[0]);
    input.line.first.y = std::stoi(coordsFirst[1]);

    input.line.second.x = std::stoi(coordsSecond[0]);
    input.line.second.y = std::stoi(coordsSecond[1]);

    return input;
}

std::vector<Input> getInput(std::unordered_map<std::string, std::string> arguments)
{
    std::vector<Input> inputs;
    std::ifstream inputFile;
    std::string line;

    inputFile.open(arguments["input"], std::ios::in);

    if (!inputFile.fail())
    {
        while (getline(inputFile, line))
        {
            const auto subStrings = splitString(line, " -> ");
            inputs.push_back(formatInput(subStrings));
        }

        inputFile.close();
    }

    return inputs;
}

std::vector<Coord> getPointsInLine(const Coord& first, const Coord& second)
{
    const int distanceX = std::abs(first.x - second.x);
    const int distanceY = std::abs(first.y - second.y);

    const int minX = std::min(first.x, second.x);
    const int minY = std::min(first.y, second.y);

    std::vector<Coord> pointsInLine;

    for (int i = 0; i < distanceX + 1; i++)
    {
        for (int j = 0; j < distanceY + 1; j++)
        {
            pointsInLine.push_back(Coord(minX + i, minY + j));
        }
    }

    return pointsInLine;
}

int getPartOneAnswer_1(std::vector<Input> inputs)
{
    std::unordered_map<Coord, int> grid;

    for (const auto& input : inputs)
    {
        const int x1 = input.line.first.x;
        const int y1 = input.line.first.y;

        const int x2 = input.line.second.x;
        const int y2 = input.line.second.y;

        if (x1 == x2 || y1 == y2)
        {
            // vertical or horizontal lines
            // interate through all coords and if it does not exist in map, add it with a value of 0
            // if it exists in map, increment the value by one
            const auto pointsInLine = getPointsInLine(input.line.first, input.line.second);

            //std::cout << "points in line with start/end: " << x1 << "," << y1 << " and " << x2 << "," << y2 << std::endl;
            for (const Coord& point : pointsInLine)
            {
                //std::cout << point.x << "," << point.y << std::endl;

                if (grid.contains(point))
                {
                    //if (point.x == 0 && point.y == 9)
                    //{
                    //    std::cout << "0,9" << std::endl;
                    //    std::cout << "grid[point] before: " << grid[point] << std::endl;
                    //}

                    grid[point]++;
                    //std::cout << "grid[point] after: " << grid[point] << std::endl;
                }
                else
                {
                    grid[point] = 1;
                }
            }
        }
    }

    int numPointWithOverlap = 0;
    for (const auto& it : grid)
    {
        //std::cout << "key: " << it.first.x << "," << it.first.y << " - value: " << it.second << std::endl;
        if (it.second >= 2)
        {
            numPointWithOverlap++;
        }
    }

    return numPointWithOverlap;
}

int getPartTwoAnswer_1()
{
    return -1;
}

void solve(std::vector<Input> inputs,
           std::unordered_map<std::string, std::string> arguments)
{
    //if (arguments.contains["
    (void)arguments;

    const int ans = getPartOneAnswer_1(inputs);

    std::cout << "part 1 answer: " << ans << std::endl;
}

int main(int argc, char* argv[])
{
    auto arguments = parseArgs(argc, argv);
    if (arguments.empty())
    {
        return 1;
    }

    auto inputs = getInput(arguments);

    if (inputs.empty())
    {
        return 1;
    }

    auto start = std::chrono::steady_clock::now();
    solve(inputs, arguments);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds" << std::endl;

    return 0;
}
