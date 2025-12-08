#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    if (!in)
    {
        cerr << "Error reading input file" << endl;
    }

    vector<pair<int64_t, int64_t>> fresh_ranges;
    string line;
    while (getline(in, line))
    {
        if (line.empty())
        {
            cout << "Found empty line" << endl;
            break;
        }
        auto pos = line.find('-');
        if (pos == string::npos)
        {
            break;
        }
        int64_t left  = stoll(line.substr(0, pos));
        int64_t right = stoll(line.substr(pos + 1, line.size() - pos));
        cout << line << endl;
        cout << "left: " << left << " right: " << right << endl;
        pair<int64_t, int64_t> p = {left, right};
        fresh_ranges.push_back(p);
    }

    vector<int64_t> ingredients;
    while (getline(in, line))
    {
        if (line.empty())
        {
            cout << "Found empty line" << endl;
            continue;
        }
        ingredients.push_back(stoll(line));
    }

    int result = 0;
    for (int64_t ingredient : ingredients)
    {
        for (auto fresh_range : fresh_ranges)
        {
            if (ingredient >= fresh_range.first && ingredient <= fresh_range.second)
            {
                result++;
                break;
            }
        }
    }
    cout << "Result: " << result << endl;
}
