#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <unistd.h>
#include <unordered_map>
#include <chrono>

#include <ctype.h>

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
    while ((arg = getopt(argc, argv, "i:p:sh")) != -1)
    {
        switch(arg)
        {
            case 'i':
                arguments["input"] = std::string(optarg);
                break;
            case 'p':
                {
                    auto part = optarg;
                    
                    if (!isdigit(std::atoi(part)))
                    {
                        std::cout << "Option -" << optopt << " requires an integer argument" << std::endl;
                        break;
                    }

                    arguments["part"] = std::string(part);
                }
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

    if (!invalid &&
        !arguments.contains("input") &&
        !arguments.contains("part"))
    {
        std::cout << "Argument -i inputFile is required" << std::endl;
    }

    return arguments;
}

std::vector<std::string> splitString(const std::string& inputString, const char* deliminator)
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

template<typename T>
std::vector<T> getInput(std::unordered_map<std::string, std::string> arguments)
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
            const auto& subStrings = splitString(line, " ");

            std::vector<BoardNumber> row;
            for (const auto& number : subStrings)
            {
                row.push_back(BoardNumber(number, false));
            }

            board.grid.push_back(row);
        }
        else
        {
            if (!board.grid.empty())
            {
                boards.push_back(board);
                board.grid.clear();
            }
        }
    }

    if (!board.grid.empty())
    {
        boards.push_back(board);
    }

    inputFile.close();

    return {drawnNumbers, boards};
}

int getPartOneAnswer_1(const std::vector<int>& drawnNumbers,
                       std::vector<Board>& boards)
{
    int sumOfBoard = 0;

    size_t i = 0;
    int drawnNumber = 0;
    for (; i < drawnNumbers.size(); i++)
    {
        drawnNumber= drawnNumbers[i];

        if (boardWon(drawnNumber, boards, sumOfBoard))
        {
            break;
        }
    }

    std::cout << "drawnNumber: " << drawnNumber << std::endl;
    std::cout << "sumOfBoard: " << sumOfBoard << std::endl;

    return drawnNumber * sumOfBoard;
}

int getPartTwoAnswer_1(const std::vector<int>& drawnNumbers,
                       std::vector<Board>& boards)
{
    int sumOfBoard = 0;

    size_t i = 0;
    int drawnNumber = 0;

    int lastDrawnNumber = 0;

    for (; i < drawnNumbers.size(); i++)
    {
        drawnNumber = drawnNumbers[i];

        if (boardWon(drawnNumber, boards, sumOfBoard))
        {
            lastDrawnNumber = drawnNumber;
        }
    }

    std::cout << "lastDrawnNumber: " << lastDrawnNumber << std::endl;
    std::cout << "sumOfBoard: " << sumOfBoard << std::endl;

    return drawnNumber * sumOfBoard;
}

template<typename T>
void solve(std::vector<T> input,
           std::unordered_map<std::string, std::string> arguments)
{
    //if (arguments.contains["
    std::cout << "" << std::endl;
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

    auto start = std::chrono::steady_clock::now();

    solve(input, arguments);

    std::chrono::duration<double> elapsed_seconds = end-start;

    return 0;
}
