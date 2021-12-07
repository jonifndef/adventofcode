#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <unistd.h>
#include <unordered_map>

struct Board
{
    std::vector<std::vector<int>> numbers;
    std::vector<std::vector<bool>> taken;
};

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

std::vector<int> splitString(const std::string& inputString, const char* deliminator)
{
    std::vector<int> numbers;

    const char* token = inputString.c_str();
    bool tokenStarted = false;
    std::string subString;
    while (*token != '\0')
    {
        if (*token != *deliminator)
        {
            tokenStarted = true;
            subString += *token;
        }
        else
        {
            if (tokenStarted)
            {
                numbers.push_back(std::stoi(subString));
                tokenStarted = false;
                subString.clear();
            }
        }
        token++;
    }

    if (tokenStarted && !subString.empty())
    {
        numbers.push_back(std::stoi(subString));
    }

    return numbers;
}

std::tuple<std::vector<int>, std::vector<Board>> getInput(std::unordered_map<std::string, std::string> arguments)
{
    std::ifstream inputFile;
    std::string line;

    inputFile.open(arguments["input"], std::ios::in);

    getline(inputFile, line);
    const auto drawnNumbers = splitString(line, ",");

    std::vector<Board> boards;
    Board board = {};
    while (getline(inputFile, line))
    {
        if (line != "")
        {
            board.numbers.push_back(splitString(line, " "));
        }
        else
        {
            if (!board.numbers.empty())
            {
                boards.push_back(board);
                board.numbers.clear();
            }
        }
    }

    if (!board.numbers.empty())
    {
        boards.push_back(board);
    }

    inputFile.close();

    return {drawnNumbers, boards};
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

bool boardWon(const int drawnNumber,
              std::vector<Board>& boards,
              int& sumOfBoard)
{
    int elementsInRowTaken = 0;
    int elementsInColumnTaken = 0;

    for (int i = 0; i < boards.size(); i++)
    {
        auto board = boards[i];

        for (int j = 0; j < board.numbers.size(); j++)
        {
            for (int k = 0; k < board.numbers[j].size(); k++)
            {
                const int num = board.numbers[j][k];
                if (num == drawnNumber)
                {
                    board.taken[j][k] = true;
                }
            }
        }
    }
}

int getPartOneAnswer_1(const std::vector<int>& drawnNumbers,
                       const std::vector<Board>& boards)
{
    int sumOfBoard = 0;

    size_t i = 0;
    for (; i < drawnNumbers.size(); i++)
    {
        const int drawnNumber= drawnNumbers[i];

        if (boardWon(drawnNumber, boards, sumOfBoard))
        {
            break;
        }
    }

    return -1;
}

int getPartTwoAnswer_1(const std::vector<std::string>& input)
{
    return 9;
}

int main(int argc, char* argv[])
{
    auto arguments = parseArgs(argc, argv);
    if (arguments.empty())
    {
        return 1;
    }

    auto [drawnNumbers, boards] = getInput(arguments);

    if (drawnNumbers.empty() || boards.empty())
    {
        return 1;
    }

    const int answer = getPartOneAnswer_1(drawnNumbers, boards);
    //const int answer = getPartTwoAnswer_1(input);

    std::cout << "Answer part 1: " << answer << std::endl;

    return 0;
}
