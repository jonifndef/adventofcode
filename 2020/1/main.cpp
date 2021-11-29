#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <unistd.h>
#include <unordered_map>

std::unordered_map<std::string, std::string> parseArgs(int argc, char* argv[])
{
    int arg;
    std::unordered_map<std::string, std::string> arguments;

    while ((arg = getopt(argc, argv, "i")) != -1)
    {
        switch(arg)
        {
            case 'i':
                arguments["input"] = optarg;
                break;
            case '?':
        }
    }

    return
}

std::vector<int> getInputs()
{
    std::vector<int> inputNumbers;
    std::ifstream inputFile;

    inputFile.open("input", std::ios::in);

    std::string line;
    while (getline(inputFile, line))
    {
        inputNumbers.push_back(std::stoi(line));
    }
    inputFile.close();

    return inputNumbers;
}

bool binarySearch(const std::vector<int>& inputNumbers,
                  unsigned const int targetValue,
                  unsigned int& lowerIndex,
                  unsigned int& upperIndex)
{
    std::cout << "lowerIndex: " << lowerIndex << std::endl;
    std::cout << "len of vector: " << inputNumbers.size() << lowerIndex << std::endl;

    const unsigned int lowerValue = inputNumbers[lowerIndex];
    const unsigned int upperValue = inputNumbers[upperIndex];

    if (lowerValue + upperValue == targetValue)
    {
        return true;
    }
    else if (lowerValue + upperValue < targetValue)
    {
        const int diff = upperIndex - lowerIndex;
        lowerIndex = diff / 2;

        return binarySearch(inputNumbers,
                            targetValue,
                            lowerIndex,
                            upperIndex);
    }
    else if (lowerValue + upperValue > targetValue)
    {
        upperIndex /= 2;
        return binarySearch(inputNumbers,
                            targetValue,
                            lowerIndex,
                            upperIndex);
    }

    return false;
}

void getAnswer(const std::vector<int>& inputNumbers,
               const unsigned int targetValue,
               int& firstNum,
               int& secondNum)
{

    unsigned int lowerIndex = 0;
    unsigned int upperIndex = inputNumbers.size() - 1;

    if (binarySearch(inputNumbers,
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

int main(int argc, char* argv[])
{
    std::vector<int> inputNumbers = getInputs();
    std::sort(inputNumbers.begin(), inputNumbers.end());

    int firstNum = 0;
    int secondNum = 0;
    int targetValue = 2000;
    getAnswer(inputNumbers, targetValue, firstNum, secondNum);

    //for (const int num : inputNumbers)
    //{
    //    std::cout << num << std::endl;
    //}

    return 0;
}
