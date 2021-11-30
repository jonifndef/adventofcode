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

// A bit more optimized than just two nested for-loops
bool search(const std::vector<int>& inputNumbers,
            const int targetValue,
            int& lowerIndex,
            int& upperIndex)
{
    int lowerValue = inputNumbers[lowerIndex];
    int upperValue = inputNumbers[upperIndex];

    while (lowerValue + upperValue != targetValue)
    {
        if (lowerValue + upperValue > targetValue)
        {
            upperIndex--;
        }
        if (lowerValue + upperValue < targetValue)
        {
            lowerIndex++;
        }

        lowerValue = inputNumbers[lowerIndex];
        upperValue = inputNumbers[upperIndex];
    }

    return true;
}

void getPartOneAnswer_1(std::vector<int>& inputNumbers,
                        int targetValue)
{
    std::sort(inputNumbers.begin(), inputNumbers.end());

    int lowerIndex = 0;
    int upperIndex = inputNumbers.size() - 1;

    if (search(inputNumbers,
               targetValue,
               lowerIndex,
               upperIndex))
    {
        int lowerValue = inputNumbers[lowerIndex];
        int upperValue = inputNumbers[upperIndex];

        std::cout << "lowerValue: " << lowerValue << std::endl;
        std::cout << "upperValue: " << upperValue << std::endl;
    }
}

void loopFunc(std::vector<int> inputNumbers,
              const int targetValue,
              int &lowerValue,
              int &upperValue)
{
    for (int i = 0; i < (int)inputNumbers.size() - 1; i++)
    {
        for (int j = i + 1; j < (int)inputNumbers.size(); j++)
        {
            lowerValue = inputNumbers[i];
            upperValue = inputNumbers[j];

            if (lowerValue + upperValue == targetValue)
            {
                return;
            }
        }
    }
}

// second, brute force nested for-loops solution for part one
void getPartOneAnswer_2(std::vector<int>& inputNumbers,
                        int targetValue)
{
    int lowerValue = 0;
    int upperValue = 0;

    loopFunc(inputNumbers, targetValue, lowerValue, upperValue);

    std::cout << "lowerValue: " << lowerValue << std::endl;
    std::cout << "upperValue: " << upperValue << std::endl;
}

void loopFunc_2(std::vector<int> inputNumbers,
                const int targetValue,
                int &firstIndex,
                int &secondIndex,
                int &thirdIndex)
{
    for (; firstIndex < secondIndex; firstIndex++)
    {
        secondIndex = firstIndex + 1;
        for (; secondIndex < thirdIndex; secondIndex++)
        {
            std::cout << "firstIndex: " << firstIndex << std::endl;
            std::cout << "secondIndex: " << secondIndex << std::endl;
            std::cout << "thirdIndex: " << thirdIndex << std::endl;

            if (inputNumbers[firstIndex] +
                inputNumbers[secondIndex] +
                inputNumbers[thirdIndex] == targetValue)
            {
                return;
            }
        }
    }
}

// A bit more optimized than just three nested for-loops
void solvePartTwo(std::vector<int> inputNumbers,
                  const int targetValue,
                  int &firstValue,
                  int &secondValue,
                  int &thirdValue)
{
    int firstIndex  = 0;
    int secondIndex = 1;
    int thirdIndex  = 2;

    firstValue  = inputNumbers[firstIndex];
    secondValue = inputNumbers[secondIndex];
    thirdValue  = inputNumbers[thirdIndex];

    while ((firstValue + secondValue + thirdValue < targetValue) &&
           (thirdIndex < (int)inputNumbers.size()))
    {
        thirdIndex++;

        thirdValue  = inputNumbers[thirdIndex];
    }

    loopFunc_2(inputNumbers, targetValue, firstIndex, secondIndex, thirdIndex);

    std::cout << "- firstIndex: " << firstIndex << std::endl;
    std::cout << "- secondIndex: " << secondIndex << std::endl;
    std::cout << "- thirdIndex: " << thirdIndex << std::endl;

    firstValue  = inputNumbers[firstIndex];
    secondValue = inputNumbers[secondIndex];
    thirdValue  = inputNumbers[thirdIndex];
}

void getPartTwoAnswer_1(std::vector<int>& inputNumbers,
                        int targetValue)
{
    std::sort(inputNumbers.begin(), inputNumbers.end());

    //for (const int num : inputNumbers)
    //{
    //    std::cout << num << std::endl;
    //}

    int firstValue  = 0;
    int secondValue = 0;
    int thirdValue  = 0;

    solvePartTwo(inputNumbers, targetValue, firstValue, secondValue, thirdValue);

    std::cout << "firstValue: "  << firstValue  << std::endl;
    std::cout << "secondValue: " << secondValue << std::endl;
    std::cout << "thirdValue: "  << thirdValue  << std::endl;
}

int main(int argc, char* argv[])
{
    auto arguments = parseArgs(argc, argv);
    if (arguments.empty())
    {
        return 1;
    }

    std::vector<int> inputNumbers = getInputs(arguments);

    int targetValue = 2020;

    //getPartOneAnswer_1(inputNumbers, targetValue);
    //getPartOneAnswer_2(inputNumbers, targetValue);
    getPartTwoAnswer_1(inputNumbers, targetValue);

    return 0;
}
