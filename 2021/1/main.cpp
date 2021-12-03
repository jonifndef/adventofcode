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

std::vector<int> getInputs(std::unordered_map<std::string, std::string> arguments)
{
    std::vector<int> inputNumbers;
    std::ifstream inputFile;

    inputFile.open(arguments["input"], std::ios::in);

    std::string line;
    while (getline(inputFile, line))
    {
        inputNumbers.push_back(std::stoi(line));
    }
    inputFile.close();

    return inputNumbers;
}

int getPartOneAnswer_1(std::vector<int>& inputNumbers)
{
    int numIncreases = 0;

    for (int i = 0; i < (int)inputNumbers.size() - 1; i++)
    {
        const int a = inputNumbers[i];
        const int b = inputNumbers[i + 1];

        if (b > a)
        {
            numIncreases++;
        }
    }

    return numIncreases;
}

int getPartTwoAnswer_1(const std::vector<int>& inputNumbers)
{
    int numIncreases = 0;

    for (int i = 0; i < (int)inputNumbers.size() - 3; i++)
    {
        const int a = inputNumbers[i];
        const int b = inputNumbers[i + 1];
        const int c = inputNumbers[i + 2];
        const int d = inputNumbers[i + 3];

        const int first  = (a + b + c);
        const int second = (b + c + d);

        if (second > first)
        {
            numIncreases++;
        }
    }

    return numIncreases;
}

int main(int argc, char* argv[])
{
    auto arguments = parseArgs(argc, argv);
    if (arguments.empty())
    {
        return 1;
    }

    std::vector<int> inputNumbers = getInputs(arguments);

    //const int answer = getPartOneAnswer_1(inputNumbers);
    const int answer = getPartTwoAnswer_1(inputNumbers);

    std::cout << "Answer part 1: " << answer << std::endl;

    return 0;
}
