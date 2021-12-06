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

std::vector<std::string> getInput(std::unordered_map<std::string, std::string> arguments)
{
    std::vector<std::string> input;
    std::ifstream inputFile;

    inputFile.open(arguments["input"], std::ios::in);

    std::string line;
    while (getline(inputFile, line))
    {
        input.push_back(line);
    }
    inputFile.close();

    return input;
}

int binToDec(long binaryNum)
{
    int decimalNum = 0;
    int base = 1;

    while (binaryNum > 0)
    {
        int reminder = binaryNum % 10;
        binaryNum /= 10;

        decimalNum += reminder * base;
        base *= 2;
    }

    return decimalNum;
}

int getPartOneAnswer_1(const std::vector<std::string>& input)
{
    std::vector<int> binaryArr;
    const int binaryArrLen = input[0].size();

    for (int i = 0; i < binaryArrLen; i++)
    {
        binaryArr.push_back(0);
    }

    for (const auto& entry : input)
    {
        for (int i = 0; i < (int)entry.size(); i++)
        {
            if (entry[i] == '0')
            {
                binaryArr[i]--;
            }
            else if (entry[i] == '1')
            {
                binaryArr[i]++;
            }
        }
    }

    std::string gammaRate;
    for (int i = 0; i < binaryArrLen; i++)
    {
        if (binaryArr[i] > 0)
        {
            gammaRate.append("1");
        }
        else if (binaryArr[i] < 0)
        {
            gammaRate.append("0");
        }
    }

    std::string epsilonRate;
    for (int i = 0; i < binaryArrLen; i++)
    {
        if (binaryArr[i] > 0)
        {
            epsilonRate.append("0");
        }
        else if (binaryArr[i] < 0)
        {
            epsilonRate.append("1");
        }
    }
    std::cout << "gammaRate: " << gammaRate << std::endl;
    std::cout << "epsilonRate: " << epsilonRate << std::endl;

    long gammaRateLong = std::stol(gammaRate);
    long epsilonRateLong = std::stol(epsilonRate);

    int gammaRateDec = binToDec(gammaRateLong);
    int epsilonRateDec = binToDec(epsilonRateLong);

    std::cout << "gammaRate in dec: " << gammaRateDec << std::endl;
    std::cout << "epsilonRate in dec: " << epsilonRateDec << std::endl;

    return gammaRateDec * epsilonRateDec;
}

int findMostCommonBit(const std::vector<std::string>& input, const int bitPosition)
{
    int mostCommonBit = 0;

    for (const auto& bitArr : input)
    {
        if (bitArr[bitPosition] == '1')
        {
            mostCommonBit++;
        }
        else
        {
            mostCommonBit--;
        }
    }

    if (mostCommonBit > 0)
    {
        return 1;
    }
    else if (mostCommonBit < 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

bool foundRating(std::vector<std::string> input, int& bitPosition)
{
    if (input.size() == 1)
    {
        return true;
    }
    else
    {
        int mostCommonBit = findMostCommonBit(input, bitPosition);
        // bump bitPosition
        return foundRating(input, bitPosition);
    }

    return false;
}

int getOxygenGeneratorRating(const std::vector<std::string>& input)
{
    auto inputCopy = input;
    int bitPosition = 0;

    if (foundRating(inputCopy, bitPosition))
    {
        long oxygenRating = std::stol(inputCopy[0]);

        return binToDec(oxygenRating);
    }

    return -1;
}

int getCO2ScrubberRating(const std::vector<std::string>& input)
{

    return -1;
}

int getPartTwoAnswer_1(const std::vector<std::string>& input)
{
    const int oxygenRating = getOxygenGeneratorRating(input);
    const int co2Rating = getCO2ScrubberRating(input);

    return oxygenRating * co2Rating;
}

int main(int argc, char* argv[])
{
    auto arguments = parseArgs(argc, argv);
    if (arguments.empty())
    {
        return 1;
    }

    auto input = getInput(arguments);
    if (input.empty())
    {
        return 1;
    }

    //const int answer = getPartOneAnswer_1(input);
    const int answer = getPartTwoAnswer_1(input);

    std::cout << "Answer part 1: " << answer << std::endl;

    return 0;
}
