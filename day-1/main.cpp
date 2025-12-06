#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

static int64_t hits_zero_during_rotation(int64_t pos, int dir, int64_t amount)
{
    if (dir == 1)
    {
        return (pos + amount) / 100;
    }
    if (pos == 0)
    {
        pos = 100;
    }
    if (pos > amount)
    {
        return 0;
    }
    return 1 + (amount - pos) / 100;
}

int main()
{
    std::ifstream in("puzzle-input.txt");
    if (!in)
    {
        std::cerr << "Could not open file\n";
        return 1;
    }

    int64_t pos    = 50;
    int64_t result = 0;

    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;

        char turn      = line.front();
        int64_t amount = std::stoll(line.substr(1));
        int dir        = (turn == 'R') ? 1 : (turn == 'L') ? -1 : 0;
        if (dir == 0)
            continue;

        result += hits_zero_during_rotation(pos, dir, amount);
        int raw = amount * dir + pos;
        pos     = (raw % 100 + 100) % 100;
    }

    std::cout << result << "\n";
}
