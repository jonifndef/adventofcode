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

struct Input
{
    std::vector<std::vector<std::pair<int, bool>>> heightmap;
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
            std::vector<std::pair<int, bool>> col;
            for (const auto& it : line)
            {
                std::stringstream strValue;
                strValue << it;
                int intValue;
                strValue >> intValue;
                col.push_back(std::pair<int, bool>(intValue, false));
            }

            input.heightmap.push_back(std::move(col));
        }

        inputFile.close();
    }
    inputs.push_back(input);

    return inputs;
}

bool traverse(Input input, int x, int y, int& height)
{
    // if taken, return false
    // beware of corners and boarders, though!
    // if up is lower and not taken
    //  traverse
    // else if left is lower and not taken
    //  traverse
    // else if right is lower and not taken
    //  traverse
    // else if down is lower and not taken
    //  traverse
    // else
    //
    //  height = input.heightmap[currPos.x][currPos.y];
    //  return true, this height is the lowest
    //
    //  Wait, don't return if we find a local minimum - just add it to a list of minimums!

    return false;
}

int getPartOneAnswer_1(const std::vector<Input>& inputs)
{
    auto& heightmap = inputs[0];
    int height = -1;

    if (traverse(heightmap, 0, 0, height))
    {
        return height;
    }

    return -1;
}

int getPartTwoAnswer_1(const std::vector<Input>& inputs)
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
