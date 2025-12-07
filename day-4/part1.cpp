#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

void print_img(const std::vector<std::vector<uint8_t>>& img)
{
    for (const auto& row : img)
    {
        for (uint8_t v : row)
        {
            std::cout << int(v);
        }
        std::cout << std::endl;
    }
}

int main()
{
    auto in = std::ifstream("input.txt");
    if (!in)
    {
        std::cerr << "Failed reading input text file" << std::endl;
        return 1;
    }

    std::vector<std::vector<uint8_t>> img;

    std::string line;
    int size = 0;
    while (std::getline(in, line))
    {
        size = line.size();
        img.push_back(std::vector<uint8_t>{});
        img.back().push_back(0);
        for (char c : line)
        {
            if (c == '.')
            {
                img.back().push_back(0);
            }
            else if (c == '@')
            {
                img.back().push_back(1);
            }
        }
        img.back().push_back(0);
    }
    std::vector<uint8_t> empty(size + 2, 0);
    img.push_back(empty);
    img.insert(img.begin(), empty);

    // print_img(img);
    int64_t result = 0;

    for (int y = 0; y < img.size(); ++y)
    {
        for (int x = 0; x < img[y].size(); ++x)
        {
            uint8_t val = img[y][x];
            if (val == 0)
            {
                continue;
            }
            int add = 0;
            for (int k_y = 0; k_y < 3; ++k_y)
            {
                for (int k_x = 0; k_x < 3; ++k_x)
                {
                    if (k_x == 1 && k_y == 1)
                        continue;
                    add += img[y + (1 - k_y)][x + (1 - k_x)];
                }
            }
            if (add < 4)
                result++;
        }
    }
    std::cout << "Result: " << result << std::endl;
}
