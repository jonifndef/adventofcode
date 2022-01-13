#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <deque>

#include <string.h>

//bool allowIncrement = true;

//struct Point
//{
//    int energyLevel = 0;
//    ?/bool firstStep = 0;
//};

struct Input
{
    std::vector<std::vector<int>> grid;
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

    if (!inputFile.fail())
    {
        Input input = {};
        while (getline(inputFile, line))
        {
            std::vector<int> col;
            for (const auto& it : line)
            {
                std::stringstream strValue;
                strValue << it;
                int intValue;
                strValue >> intValue;
                col.push_back(intValue);
            }
            input.grid.push_back(col);
        }

        inputFile.close();
        inputs.push_back(input);
    }

    return inputs;
}

void printGrid(const std::vector<std::vector<int>>& grid)
{
    for (const auto& col : grid)
    {
        for (const auto& it : col)
        {
            std::cout << it;
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

bool withinBorders(const std::vector<std::vector<int>>& grid,
                   int x,
                   int y)
{
    return ((x >= 0 && x < (int)grid.size()) &&
            (y >= 0 && y < (int)grid[x].size()));
}

void incrementEnergy(std::vector<std::vector<int>>& grid,
                     int& numFlashes,
                     int x,
                     int y)
{
    // we only allow incrementations of 0 in a new step! While we are in a step, stop incrementing if 0
    
    std::deque<std::pair<int, int>> energyQueue;
    int& energyLevel = grid[x][y];

    if (energyLevel > 9)
    {
        energyLevel = 0;  

        energyQueue.push_back(std::pair<int, int>(x - 1, y - 1));
        energyQueue.push_back(std::pair<int, int>(x, y - 1));
        energyQueue.push_back(std::pair<int, int>(x + 1, y - 1));
        energyQueue.push_back(std::pair<int, int>(x + 1, y));
        energyQueue.push_back(std::pair<int, int>(x + 1, y + 1));
        energyQueue.push_back(std::pair<int, int>(x, y + 1));
        energyQueue.push_back(std::pair<int, int>(x - 1, y + 1));
        energyQueue.push_back(std::pair<int, int>(x - 1, y));
    }

    while (!energyQueue.empty())
    {
        auto point = energyQueue.front();
        energyQueue.pop_front();

        if (!withinBorders(grid, point.first, point.second))
        {
            continue;
        }

        int& energyLevel = grid[point.first][point.second];

        if (energyLevel != 0)
        {
            energyLevel++;

            if (energyLevel > 9)
            {
                numFlashes++;
                energyLevel = 0;
                //std::cout << "pos " << point.first << ", " << point.second << " flashed!" << std::endl;
                //printGrid(grid);

                //if ((y > 0 && y < 5) && (x > 3))
                //{
                //    printGrid(grid);
                //}

                // clockwise starting from top left
                energyQueue.push_back(std::pair<int, int>(x - 1, y - 1));
                energyQueue.push_back(std::pair<int, int>(x, y - 1));
                energyQueue.push_back(std::pair<int, int>(x + 1, y - 1));
                energyQueue.push_back(std::pair<int, int>(x + 1, y));
                energyQueue.push_back(std::pair<int, int>(x + 1, y + 1));
                energyQueue.push_back(std::pair<int, int>(x, y + 1));
                energyQueue.push_back(std::pair<int, int>(x - 1, y + 1));
                energyQueue.push_back(std::pair<int, int>(x - 1, y));
            }
        }
    }
}

void runStep(std::vector<std::vector<int>>& grid,
             int& numFlashes)
{
    for (int x = 0; x < (int)grid.size(); x++)
    {
        for (int y = 0; y < (int)grid[x].size(); y++)
        {
            //incrementEnergy(grid, numFlashes, x, y);
            grid[x][y]++;
        }
    }

    std::cout << "just incremented every point in a new step!" << std::endl;
    printGrid(grid);

    for (int x = 0; x < (int)grid.size(); x++)
    {
        for (int y = 0; y < (int)grid[x].size(); y++)
        {
            incrementEnergy(grid, numFlashes, x, y);
        }
    }
}

int getPartOneAnswer_1(const std::vector<Input>& inputs)
{
    auto grid = inputs[0].grid;
    int numFlashes = 0;
    (void)numFlashes;

    int numSteps = 2;
    for (int i = 0; i < numSteps; i++)
    {
        runStep(grid, numFlashes);
    }

    printGrid(grid);

    return -1;
}

long getPartTwoAnswer_1(const std::vector<Input>& inputs)
{
    (void)inputs;

    return -1;
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
