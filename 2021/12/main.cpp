#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include <deque>

#include <string.h>

struct NodeData
{
    bool explored = false;
    std::vector<std::string> connections;
};

struct Input
{
    std::unordered_map<std::string, NodeData> nodes;
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

void formatInput(const std::vector<std::string>& subStrings,
                 std::unordered_map<std::string, NodeData>& nodes)
{
    if (nodes.contains(subStrings[0]))
    {
        if (subStrings[1] != "start")
        {
            nodes[subStrings[0]].connections.push_back(subStrings[1]);
        }
    }
    else
    {
        NodeData nodeData = {};
        if (subStrings[1] != "start")
        {
            nodeData.connections.push_back(subStrings[1]);
        }

        nodes[subStrings[0]] = nodeData;
    }

    if (nodes.contains(subStrings[1]))
    {
        if (subStrings[0] != "start")
        {
            nodes[subStrings[1]].connections.push_back(subStrings[0]);
        }
    }
    else
    {
        if (subStrings[1] != "end")
        {
            NodeData nodeData = {};

            if (subStrings[0] != "start")
            {
                nodeData.connections.push_back(subStrings[0]);
            }

            nodes[subStrings[1]] = nodeData;
        }
    }
}

std::vector<Input> getInput(std::unordered_map<std::string, std::string> arguments)
{
    std::ifstream inputFile;
    std::string line;
    std::vector<Input> inputs;
    Input input = {};
    auto& nodes = input.nodes;

    inputFile.open(arguments["input"], std::ios::in);

    if (!inputFile.fail())
    {
        while (getline(inputFile, line))
        {
            auto subStrings = splitString(line, "-");
            if (subStrings.size() > 2)
            {
                return inputs;
            }

            formatInput(subStrings, nodes);
        }

        inputFile.close();
    }

    inputs.push_back(input);
    return inputs;
}

int getPartOneAnswer_1(const std::vector<Input>& inputs)
{
    const auto& nodes = inputs[0].nodes;

    std::deque<std::pair<std::string, NodeData>> nodeQueue;

    auto start = nodes.find("start")->second;

    for (const auto& it : nodes)
    {
        std::cout << "key: " << it.first << ", connections: ";
        for (const auto& conn : it.second.connections)
        {
            std::cout << conn << ", ";
        }
        std::cout << std::endl;
    }

    // check connections of start, then add each to the queue
    // how to check if we've been on the lowercase node?
    // and how to "remember" the path we've taken?
    // some sort of backtracking? Is this possible with a queue?
    // include a vector of nodes when inserting into the queue? std::pair<node, visitednodes>?
    // we have a problem, the node "b" only has the connections "d" and "end", but it is also connedted to "A"
    // how to know which nodes are at the same level as the current one, and not one step "up"?
    // E.g. if we choose to include "A" in the node b's connections, what's stopping us from adding "start" or similar? How do we know if we are going "sideways" or "upwards"?
    // We should be able to go "upwards" in all cases except when it's "start". So just add the key to the connections

    //for (const auto& con : start.connections)
    //{
    //    nodeQueue.push_back()
    //}



    return -1;
}

long getPartTwoAnswer_1(const std::vector<Input>& inputs)
{
    (void)inputs;

    return -1;
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

    //const auto& nodes = inputs[0].nodes;
    //for (const auto& it : nodes)
    //{
    //    std::cout << "key: " << it.first << ", values: ";
    //    for (const auto& con : it.second.connections)
    //    {
    //        std::cout << con << ",";
    //    }
    //    std::cout << std::endl;
    //}

    auto start = std::chrono::steady_clock::now();
    solve(inputs, arguments);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds" << std::endl;

    return 0;
}
