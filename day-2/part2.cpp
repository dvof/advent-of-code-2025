#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

int main()
{
    std::ifstream in("input.txt");
    if (!in)
    {
        std::cerr << "Could not open file\n";
        return 1;
    }

    std::string line;
    std::getline(in, line);

    std::vector<std::pair<int64_t, int64_t>> pairs;

    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ','))
    {
        auto dash = token.find('-');
        int64_t a = std::stoll(token.substr(0, dash));
        int64_t b = std::stoll(token.substr(dash + 1));
        pairs.emplace_back(a, b);
    }

    std::cout << "Read " << pairs.size() << " pairs\n";

    int64_t result = 0;

    for (auto pair : pairs)
    {
        for (int64_t i = pair.first; i <= pair.second; i++)
        {
            // int digits    = (i == 0) ? 1 : int(std::log10(double(i))) + 1;
            // int half      = digits / 2;
            // int even      = (i % 2 == 0) ? 0 : 1;
            // int64_t left  = i / (int64_t)pow(10, half + even);
            // int64_t right = i % (int64_t)pow(10, half);
            // if (left == right)
            // {
            //     std::cout << "value: " << i << " left: " << left << " right: " << right
            //               << std::endl;
            //     result += i;
            // }
            auto str = std::to_string(i);
            int size = str.size();
            // if (size % 2 != 0)
            // {
            //     continue;
            // }
            int half = size / 2;
            for (int j = 1; j <= half; j++)
            {
                if (size % j != 0)
                {
                    continue;
                }
                auto compare  = str.substr(0, j);
                bool repeated = true;
                for (int k = 1; k < size / j; k++)
                {
                    if (compare != str.substr(k * j, j))
                    {
                        repeated = false;
                        break;
                    }
                }
                if (repeated)
                {
                    std::cout << "i: " << i << std::endl;
                    result += i;
                    break;
                }
            }

            // auto left  = str.substr(0, half);
            // auto right = str.substr(size - half, size);
            // if (left == right)
            // {
            //     std::cout << "value: " << i << " left: " << left << " right: " << right
            //               << std::endl;
            //     result += i;
            // }
        }
    }
    std::cout << result << std::endl;
}
