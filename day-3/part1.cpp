#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
// #include <array>

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
        // std::cout << line << std::endl;
        if (line.empty())
        {
            continue;
        }
        // std::array<int, 2> joltages{};
        int first  = 0;
        int second = 0;
        for (int i = 0; i < line.size(); ++i)
        {
            int d = line[i] - '0';
            if (d > first && i < (line.size() - 1))
            {
                first  = d;
                second = 0;
                continue;
            }
            if (d > second)
            {
                second = d;
            }
        }
        // std::cout << first * 10 + second << std::endl;

        result += first * 10 + second;
        // if (result > 500)
        //     break;
    }

    std::cout << result << std::endl;
}
