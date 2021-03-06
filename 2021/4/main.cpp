#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <unistd.h>
#include <unordered_map>
#include <chrono>

struct BoardNumber
{
    BoardNumber(int number, bool taken) : number(number), taken(taken)
    {

    }

    int number = 0;
    bool taken = false;
};

struct Board
{
    int getSumOfBoard()
    {
        int sumOfBoard = 0;

        for (const auto& row : this->grid)
        {
            for (const auto& boardNumber : row)
            {
                if (!boardNumber.taken)
                {
                    sumOfBoard += boardNumber.number;
                }
            }
        }

        return sumOfBoard;
    }

    bool hasBingo()
    {
        //int numTakenCol = 0;
        
        if (this->hasHadBingo)
        {
            return false;
        }

        for (size_t i = 0; i < this->grid.size(); i++)
        {
            int numTakenRow = 0;
            int numTakenCol = 0;

            for (size_t j = 0; j < this->grid[i].size(); j++)
            {
                if (this->grid[i][j].taken)
                {
                    numTakenRow++;
                }

                if (this->grid[j][i].taken)
                {
                    numTakenCol++;
                }

                if (numTakenRow == 5 || numTakenCol == 5)
                {
                    this->hasHadBingo = true;
                    return true;
                }
            }
        }

        return false;
    }

    std::vector<std::vector<BoardNumber>> grid;
    bool hasHadBingo;
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
    for (size_t i = 0; i < boards.size(); i++)
    {
        auto &board = boards[i];

        if (board.hasHadBingo)
        {
            continue;
        }

        for (size_t j = 0; j < board.grid.size(); j++)
        {
            for (size_t k = 0; k < board.grid[j].size(); k++)
            {
                const int num = board.grid[j][k].number;
                if (num == drawnNumber)
                {
                    board.grid[j][k].taken = true;
                }
            }
        }
    }

    for (size_t i = 0; i < boards.size(); i++)
    {
        Board& board = boards[i];

        if (board.hasBingo())
        {
            sumOfBoard = board.getSumOfBoard();
            return true;
        }
    }

    return false;
}

int boardWonPartTwo(const int drawnNumber,
                    std::vector<Board>& boards)
{
    int sumOfBoard = 0;

    for (size_t i = 0; i < boards.size(); i++)
    {
        auto &board = boards[i];

        if (board.hasHadBingo)
        {
            continue;
        }

        for (size_t j = 0; j < board.grid.size(); j++)
        {
            for (size_t k = 0; k < board.grid[j].size(); k++)
            {
                const int num = board.grid[j][k].number;
                if (num == drawnNumber)
                {
                    board.grid[j][k].taken = true;

                    if (board.hasBingo())
                    {
                        sumOfBoard = board.getSumOfBoard();
                    }
                }
            }
        }
    }

    return sumOfBoard;
}

int getPartOneAnswer_1(const std::vector<int>& drawnNumbers,
                       std::vector<Board>& boards)
{
    int sumOfBoard = 0;

    size_t i = 0;
    int drawnNumber = 0;
    for (; i < drawnNumbers.size(); i++)
    {
        drawnNumber = drawnNumbers[i];

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
    size_t i = 0;
    int drawnNumber = 0;
    int lastDrawnNumber = 0;
    int sumOfBoard = 0;
    int lastSumOfBoard = 0;

    for (; i < drawnNumbers.size(); i++)
    {
        drawnNumber = drawnNumbers[i];

        sumOfBoard = boardWonPartTwo(drawnNumber, boards);

        if (sumOfBoard)
        {
            lastDrawnNumber = drawnNumber;
            lastSumOfBoard = sumOfBoard;
        }
    }

    return lastDrawnNumber * lastSumOfBoard;
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

    // Alt solution: put each board in an std::unordered_map, with the numbers as keys and position as value.
    // Then, a vector with 10 places for the 10 possible rows+columns that are incremented for each taken number,
    auto start = std::chrono::steady_clock::now();
    //const int answer = getPartOneAnswer_1(drawnNumbers, boards);
    const int answer = getPartTwoAnswer_1(drawnNumbers, boards);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "Answer part 1: " << answer << std::endl;
    std::cout << "elapsed time: " << elapsed_seconds.count() << std::endl;

    return 0;
}
