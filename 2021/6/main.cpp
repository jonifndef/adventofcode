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

struct Input
{
    std::vector<int> fishes;
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

    for (const auto& subString : subStrings)
    {
        input.fishes.push_back(std::stoi(subString));
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
            const auto subStrings = splitString(line, ",");
            inputs.push_back(formatInput(subStrings));
        }

        inputFile.close();
    }

    return inputs;
}

int getPartOneAnswer_1(const std::vector<Input>& inputs)
{
    // just one row in inputs this time
    std::vector<int> fishes = inputs[0].fishes;

    const size_t maxDays = 80;

    size_t lenOfFishes = fishes.size();
    for (size_t days = 0; days < maxDays; days++)
    {
        for (size_t i = 0; i < lenOfFishes; i++)
        {
            if (fishes[i] == 0)
            {
                fishes[i] = 6;
                fishes.push_back(8);
            }
            else
            {
                fishes[i]--;
            }
        }

        lenOfFishes = fishes.size();
    }

    return fishes.size();
}

unsigned long long getPartTwoAnswer_1(const std::vector<Input>& inputs)
{
    std::unordered_map<int, int> fishes;

    for (const auto& fish : inputs[0].fishes)
    {
        if (fishes.contains(int(fish)))
        {
            fishes[int(fish)]++;
        }
        else
        {
            fishes[int(fish)] = 1;
        }
    }

    const size_t maxDays = 256;
    for (size_t days = 0; days < maxDays; days++)
    {
        std::unordered_map<int, int> fishesCopy;
        for (const auto& it : fishes)
        {
            const auto& key = it.first;
            const auto& val = it.second;

            if (key == 0)
            {
                fishesCopy[8] += val;
                fishesCopy[6] += val;
            }
            else
            {
                fishesCopy[key - 1] += val;
            }
        }

        fishes = fishesCopy;
    }

    unsigned long long sumOfFishes = 0;
    for (const auto& it : fishes)
    {
        sumOfFishes += it.second;
    }

    return sumOfFishes;
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
