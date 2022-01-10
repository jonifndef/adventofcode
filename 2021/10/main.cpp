#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <unordered_map>
#include <chrono>
#include <stack>

#include <string.h>

struct Input
{
    std::vector<char> line;
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
    (void)subStrings;
    Input input = {};

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
            Input input = {};
            for (const auto& it : line)
            {
                //std::stringstream strValue;
                //strValue << it;
                //int intValue;
                //strValue >> intValue;
                //Point point = {};
                //point.height = intValue;
                //col.push_back(point);

                input.line.push_back(it);
            }

            inputs.push_back(input);
        }

        inputFile.close();
    }

    return inputs;
}

bool isOpeningToken(const char token)
{
    return (token == '(' ||
            token == '[' ||
            token == '{' ||
            token == '<');
}

char getClosingToken(const char token)
{
    if (token == '(') return ')';
    if (token == '[') return ']';
    if (token == '{') return '}';
    if (token == '<') return '>';
    else return '\0';
}

int pointsForToken(const char token)
{
    if (token == ')') return 3;
    if (token == ']') return 57;
    if (token == '}') return 1197;
    if (token == '>') return 25137;
    else return 0;
}

int pointsForTokenPartTwo(const char token)
{
    if (token == ')') return 1;
    if (token == ']') return 2;
    if (token == '}') return 3;
    if (token == '>') return 4;
    else return 0;
}

int getLinePoints(const std::vector<char>& line)
{
    std::stack<char> tokens;

    for (const char token : line)
    {
        if (isOpeningToken(token))
        {
            tokens.push(token);
        }
        else
        {
            if (token == getClosingToken(tokens.top()))
            {
                if (!tokens.empty())
                {
                    tokens.pop();
                }
                else
                {
                    std::cout << "warning, cannot pop empty stack!" << std::endl;
                }
            }
            else
            {
                return pointsForToken(token);
            }
        }
    }

    return 0;
}

long getLinePointsPartTwo(const std::vector<char>& line)
{
    std::stack<char> tokens;

    for (const char token : line)
    {
        if (isOpeningToken(token))
        {
            tokens.push(token);
        }
        else
        {
            if (token == getClosingToken(tokens.top()))
            {
                if (!tokens.empty())
                {
                    tokens.pop();
                }
                else
                {
                    std::cout << "warning, cannot pop empty stack!" << std::endl;
                }
            }
            else
            {
                return 0;
            }
        }
    }

    if (!tokens.empty())
    {
        long sum = 0;
        int stackSize = tokens.size();
        for (int i = 0; i < stackSize; i++)
        {
            char token = tokens.top();
            tokens.pop();

            sum *= 5;
            sum += pointsForTokenPartTwo(getClosingToken(token));
        }

        return sum;
    }

    return 0;
}

int getPartOneAnswer_1(const std::vector<Input>& inputs)
{
    std::vector<int> pointList;

    for (const auto& it : inputs)
    {
        int points = (getLinePoints(it.line));

        if (points)
        {
            pointList.push_back(points);
        }
    }

    int sum = 0;
    for (const auto& it : pointList)
    {
        sum += it;
    }

    return sum;
}

long getPartTwoAnswer_1(const std::vector<Input>& inputs)
{
    std::vector<long> pointList;

    for (const auto& it : inputs)
    {
        long points = (getLinePointsPartTwo(it.line));

        if (points)
        {
            pointList.push_back(points);
        }
    }

    std::sort(pointList.begin(), pointList.end());
    return pointList[pointList.size() / 2];
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
