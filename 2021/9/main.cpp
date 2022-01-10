#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <unistd.h>
#include <unordered_map>
#include <chrono>
#include <numeric>
#include <sstream>

#include <ctype.h>
#include <string.h>
#include <math.h>

struct Point
{
    int height = 0;
    bool traversed = false;
    bool counted = false;
};

struct Input
{
    std::vector<std::vector<Point>> heightmap;
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
    (void)subStrings;
    Input input = {};

    return input;
}

std::vector<Input> getInput(std::unordered_map<std::string, std::string> arguments)
{
    std::vector<Input> inputs;
    std::ifstream inputFile;
    std::string line;

    inputFile.open(arguments["input"], std::ios::in);

    Input input = {};
    if (!inputFile.fail())
    {
        while (getline(inputFile, line))
        {
            std::vector<Point> col;
            for (const auto& it : line)
            {
                std::stringstream strValue;
                strValue << it;
                int intValue;
                strValue >> intValue;
                Point point = {};
                point.height = intValue;
                col.push_back(point);
            }

            input.heightmap.push_back(std::move(col));
        }

        inputFile.close();
    }
    inputs.push_back(input);

    return inputs;
}

bool checkBoarders(const Input& input, int x, int y)
{
    return ((x < (int)input.heightmap.size() && x >= 0) &&
            (y < (int)input.heightmap[x].size() && y >= 0));
}

bool higher(const Input& input, const Point& currPoint, int x, int y)
{
    if (checkBoarders(input, x, y))
    {
        if (input.heightmap[x][y].height > currPoint.height)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool traversable(const Input& input, int x, int y)
{
    if (checkBoarders(input, x, y))
    {
        if (!input.heightmap[x][y].traversed)
        {
            return true;
        }
    }

    return false;
}

bool countable(const Input& input, int x, int y)
{
    if (checkBoarders(input, x, y))
    {
        const Point& point = input.heightmap[x][y];
        if (!point.counted && point.height != 9)
        {
            return true;
        }
    }

    return false;
}

void count(Input& input,
           int& sumCount,
           int x,
           int y)
{
    Point& point = input.heightmap[x][y];
    sumCount++;
    point.counted = true;

    if (countable(input, x + 1, y))
    {
        count(input, sumCount, x + 1, y);
    }
    if (countable(input, x - 1, y))
    {
        count(input, sumCount, x - 1, y);
    }
    if (countable(input, x, y + 1))
    {
        count(input, sumCount, x, y + 1);
    }
    if (countable(input, x, y - 1))
    {
        count(input, sumCount, x, y - 1);
    }
}

void traverse(Input &input,
              std::vector<int>& localMins,
              int x,
              int y)
{
    Point& point = input.heightmap[x][y];
    point.traversed = true;

    if (higher(input, point, x + 1, y) &&
        higher(input, point, x - 1, y) &&
        higher(input, point, x, y + 1) &&
        higher(input, point, x, y - 1))
    {
        localMins.push_back(point.height + 1);
    }

    if (traversable(input, x + 1, y))
    {
        traverse(input, localMins, x + 1, y);
    }
    if (traversable(input, x - 1, y))
    {
        traverse(input, localMins, x - 1, y);
    }
    if (traversable(input, x, y + 1))
    {
        traverse(input, localMins, x, y + 1);
    }
    if (traversable(input, x, y - 1))
    {
        traverse(input, localMins, x, y - 1);
    }
}

void traversePartTwo(Input &input,
                     std::vector<int>& basins,
                     int x,
                     int y)
{
    Point& point = input.heightmap[x][y];
    point.traversed = true;
    int sumCount = 0;

    if (higher(input, point, x + 1, y) &&
        higher(input, point, x - 1, y) &&
        higher(input, point, x, y + 1) &&
        higher(input, point, x, y - 1))
    {
        count(input, sumCount, x, y);
        basins.push_back(sumCount);
    }

    if (traversable(input, x + 1, y))
    {
        traversePartTwo(input, basins, x + 1, y);
    }
    if (traversable(input, x - 1, y))
    {
        traversePartTwo(input, basins, x - 1, y);
    }
    if (traversable(input, x, y + 1))
    {
        traversePartTwo(input, basins, x, y + 1);
    }
    if (traversable(input, x, y - 1))
    {
        traversePartTwo(input, basins, x, y - 1);
    }
}

int getPartOneAnswer_1(const std::vector<Input>& inputs)
{
    Input input = inputs[0];
    std::vector<int> localMins;

    traverse(input, localMins, 0, 0);

    int sum = 0;
    for (const auto& it : localMins)
    {
        sum += it;
    }

    return sum;
}

int getPartTwoAnswer_1(const std::vector<Input>& inputs)
{
    Input input = inputs[0];
    std::vector<int> basins;

    traversePartTwo(input, basins, 0, 0);

    std::sort(basins.begin(), basins.end(), []
        (int a, int b) {
            return a > b;
        });

    return basins[0] * basins[1] * basins[2];
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
        const auto ans = getPartTwoAnswer_1(inputs);
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
