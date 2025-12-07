#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <array>

int main()
{
    auto in = std::ifstream("input.txt");
    if (!in)
    {
        std::cerr << "Error reading input text file" << std::endl;
        return 1;
    }

    std::string line;
    int64_t result = 0;

    while (std::getline(in, line))
    {
        std::cout << line << std::endl;
        if (line.empty())
        {
            continue;
        }
        std::array<int, 12> jlt{};
        // int first  = 0;
        // int second = 0;
        for (int i = 0; i < line.size(); ++i)
        {
            int d = line[i] - '0';
            for (int j = 0; j < jlt.size(); j++)
            {
                if (d > jlt.at(j) && i < (line.size() - (11 - j)))
                {
                    jlt.at(j) = d;
                    std::fill(jlt.begin() + j + 1, jlt.end(), 0);
                    break;
                }
            }
        }
        // std::cout << first * 10 + second << std::endl;

        for (int j = 0; j < jlt.size(); j++)
        {
            result += jlt.at(j) * std::pow(10, 11 - j);
        }
    }

    std::cout << result << std::endl;
}
