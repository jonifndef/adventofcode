#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <unistd.h>
#include <unordered_map>
#include <chrono>
#include <numeric>

#include <ctype.h>
#include <string.h>
#include <math.h>

// 3 digits use 6 segments: 0 6 9
// 1 digit  use 2 segments: 1
// 1 digit  use 4 segments: 4
// 3 digits use 5 segments: 2 3 5
// 1 digit  use 3 segments: 7
// 1 digit  use 7 segments: 8

// for 6 segments:
// if it has 1 segments in common 1, then it's a 6.
// if it has 4 segments in common with 4, then it's a 9, if lower, it's a 0

// for 5 segments:
// if it has 2 segments in common 1, then it's a 3
// if it has 3 segments in common with 4, it's a 5, if lower, it's a 2

const std::vector<int> numDigitsInNumber = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

struct Input
{
    std::pair<std::vector<std::string>, std::vector<std::string>> entry;
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
    Input input = {};

    if (subStrings.size() == 2)
    {
        input.entry.first  = splitString(subStrings[0], " ");
        input.entry.second = splitString(subStrings[1], " ");
    }

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
            const auto subStrings = splitString(line, " | ");
            inputs.push_back(formatInput(subStrings));
        }

        inputFile.close();
    }

    return inputs;
}

int getPartOneAnswer_1(const std::vector<Input>& inputs)
{
    int occurrences = 0;

    for (const auto& it : inputs)
    {
        for (const auto& segmentSignals : it.entry.second)
        {
            const int len = segmentSignals.size();
            if (len == numDigitsInNumber[1] ||
                len == numDigitsInNumber[4] ||
                len == numDigitsInNumber[7] ||
                len == numDigitsInNumber[8])
            {
                occurrences++;
            }
        }
    }

    return occurrences;
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
