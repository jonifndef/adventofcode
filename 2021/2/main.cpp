#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <unistd.h>
#include <unordered_map>

std::unordered_map<std::string, std::string> parseArgs(int argc, char* argv[])
{
    std::unordered_map<std::string, std::string> arguments;

    const static std::string usage =
        "Usage: aoc -i inputfile [-s solution_number]\n"
        "\t-i inputfile: specify inputfile. Required\n"
        "\t-s solution_number: specify solution number if multiple are available\n"
        "\t-h: prints this message";

    bool invalid = false;
    int arg;
    while ((arg = getopt(argc, argv, "i:sh")) != -1)
    {
        switch(arg)
        {
            case 'i':
                arguments["input"] = std::string(optarg);
                break;
            case 's':
                arguments["solution"] = std::string(optarg);
                break;
            case 'h':
                std::cout << usage << std::endl;
                break;
            case '?':
                if (optopt == 'i')
                {
                    std::cout << "Option -" << optopt << " requires an argument" << std::endl;
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

    if (!invalid && !arguments.contains("input"))
    {
        std::cout << "Argument -i inputFile is required" << std::endl;
    }

    return arguments;
}

std::vector<std::string> splitString(const std::string& inputString, const char* deliminator)
{
    std::vector<std::string> subStrings; 

    size_t pos = 0;
    size_t prevPos = 0;

    while ((pos = inputString.find(deliminator, pos)) != std::string::npos)
    {
        const std::string subString = inputString.substr(prevPos, pos - prevPos);
        subStrings.push_back(subString);

        prevPos = ++pos;
    }
    const std::string subString = inputString.substr(prevPos, pos - prevPos);
    subStrings.push_back(subString);

    return subStrings;
}

std::vector<std::pair<std::string, int>> getInput(std::unordered_map<std::string, std::string> arguments)
{
    std::vector<std::pair<std::string, int>> input;
    std::ifstream inputFile;

    inputFile.open(arguments["input"], std::ios::in);

    std::string line;
    while (getline(inputFile, line))
    {
        std::string direction = splitString(line, " ")[0];
        int amount = std::stoi(splitString(line, " ")[1]);

        auto entry = std::make_pair(direction, amount);
        input.push_back(entry);
    }
    inputFile.close();

    return input;
}

int getPartOneAnswer_1(const std::vector<std::pair<std::string, int>>& input)
{
    int horizontalPos = 0;
    int depth= 0;

    for (const auto& entry : input)
    {
        if (entry.first == "forward")
        {
            horizontalPos += entry.second;
        }
        else if (entry.first == "up")
        {
            depth -= entry.second;
        }
        else if (entry.first == "down")
        {
            depth += entry.second;
        }
    }

    std::cout << "horizontalPos: " << horizontalPos << std::endl;
    std::cout << "depth: " << depth << std::endl;

    return horizontalPos * depth;
}

int getPartTwoAnswer_1(const std::vector<std::pair<std::string, int>>& input)
{
    int horizontalPos = 0;
    int depth = 0;
    int aim = 0;

    for (const auto& entry : input)
    {
        if (entry.first == "forward")
        {
            horizontalPos += entry.second;
            depth += aim * entry.second;
        }
        else if (entry.first == "up")
        {
            aim -= entry.second;
        }
        else if (entry.first == "down")
        {
            aim += entry.second;
        }
    }

    std::cout << "horizontalPos: " << horizontalPos << std::endl;
    std::cout << "depth: " << depth << std::endl;
    std::cout << "aim: " << aim << std::endl;

    return horizontalPos * depth;
}

int main(int argc, char* argv[])
{
    auto arguments = parseArgs(argc, argv);
    if (arguments.empty())
    {
        return 1;
    }

    auto input = getInput(arguments);

    //const int answer = getPartOneAnswer_1(input);
    const int answer = getPartTwoAnswer_1(input);

    std::cout << "Answer part 1: " << answer << std::endl;

    return 0;
}
