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
    int x = 0;
    int y = 0;
};

struct Input
{
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
                        std::cout << "Invalid argument value for argument "
                                  << static_cast<char>(optopt) << std::endl;
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
            arguments.clear();
        }
        if (!arguments.count("part"))
        {
            std::cout << "Argument -p is required" << std::endl;
            arguments.clear();
        }
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

int getPartOneAnswer_1()
{
    return -1;
}

int getPartTwoAnswer_1()
{
    return -1;
}

void solve(std::vector<Input> inputs,
           std::unordered_map<std::string, std::string> arguments)
{
    //if (arguments.contains["
    (void)inputs;
    (void)arguments;

    std::cout << "" << std::endl;
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
