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

    bool operator!=(const Coord& other) const
    {
        return (this->x != other.x || this->y != other.y);
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

    int arg;
    while ((arg = getopt(argc, argv, "i:p:s::h")) != -1)
    {
        switch(arg)
        {
            case 'i':
                arguments["input"] = std::string(optarg);
                break;
            case 'p':
                {
                    int part = atoi(optarg);
                    if (part < 1 || part > 3)
                    {
                        std::cout << "Invalid argument value for argument -"
                                  << static_cast<char>(arg) << std::endl;
                        break;
                    }

                    arguments["part"] = std::to_string(part);
                }
                break;
            case 's':
                arguments["solution"] = std::string(optarg);
                break;
            case 'h':
                arguments.clear();
                break;
            case '?':
                if (optopt == 'i')
                {
                    std::cout << "Option -" << static_cast<char>(optopt) << " requires an argument" << std::endl;
                }
                if (optopt == 'p')
                {
                    std::cout << "Option -" << static_cast<char>(optopt) << " requires an integer argument" << std::endl;
                }
                else
                {
                    arguments.clear();
                    std::cout << "Invalid argument" << std::endl;
                    std::cout << usage << std::endl;
                }
                break;
            default:
                break;
        }
    }

    if (!arguments.count("input") || !arguments.count("part"))
    {
        if (!arguments.count("input"))
        {
            std::cout << "Argument -i is required" << std::endl;
        }
        if (!arguments.count("part"))
        {
            std::cout << "Argument -p is required" << std::endl;
        }

        arguments.clear();
        std::cout << usage << std::endl;
    }

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

std::vector<Coord> getPointsInDiagonalLine(const Coord& first, const Coord& second)
{
    // 8,0 -> 0,8
    //
    // 8,0 7,1 6,2 5,3 4,4 3,5 2,6, 1,7, 0,8

    const int minX = std::min(first.x, second.x);
    Coord startPoint(0, 0);
    Coord endPoint(0, 0);

    if (first.x == minX)
    {
        startPoint = first;
        endPoint = second;
    }
    else
    {
        startPoint = second;
        endPoint = first;
    }

    std::vector<Coord> pointsInLine;

    while (startPoint != endPoint)
    {
        pointsInLine.push_back(startPoint);

        startPoint.x++;
        if (startPoint.y < endPoint.y)
        {
            startPoint.y++;
        }
        else
        {
            startPoint.y--;
        }
    }
    pointsInLine.push_back(startPoint);

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
            const auto pointsInLine = getPointsInLine(input.line.first, input.line.second);

            for (const Coord& point : pointsInLine)
            {
                if (grid.contains(point))
                {
                    grid[point]++;
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
        if (it.second >= 2)
        {
            numPointWithOverlap++;
        }
    }

    return numPointWithOverlap;
}

int getPartTwoAnswer_1(const std::vector<Input>& inputs)
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
            const auto pointsInLine = getPointsInLine(input.line.first, input.line.second);

            for (const Coord& point : pointsInLine)
            {
                if (grid.contains(point))
                {
                    grid[point]++;
                }
                else
                {
                    grid[point] = 1;
                }
            }
        }
        else
        {
            // diagonal lines
            const auto pointsInDiagonalLine = getPointsInDiagonalLine(input.line.first, input.line.second);
            for (const Coord& point : pointsInDiagonalLine)
            {
                if (grid.contains(point))
                {
                    grid[point]++;
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
        if (it.second >= 2)
        {
            numPointWithOverlap++;
        }
    }

    return numPointWithOverlap;
}

void solve(std::vector<Input> inputs,
           std::unordered_map<std::string, std::string> arguments)
{

    if (std::stoi(arguments["part"]) == 1)
    {
        const int ans = getPartOneAnswer_1(inputs);
        std::cout << "part 1 answer: " << ans << std::endl;
    }
    else if (std::stoi(arguments["part"]) == 2)
    {
        const int ans = getPartTwoAnswer_1(inputs);
        std::cout << "part 2 answer: " << ans << std::endl;
    }
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
