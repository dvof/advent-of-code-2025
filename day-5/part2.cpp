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
        return 1;
    }

    vector<pair<int64_t, int64_t>> fresh_ranges;
    string line;
    int64_t result = 0;
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
        // cout << "left: " << left << " right: " << right << endl;
        // int64_t temp = (right - left) + 1;
        // cout << "r - l: " << temp << endl;
        // result += temp;
        pair<int64_t, int64_t> p = {left, right};
        // 397147209543494
        // 438538168450414

        // Result: 349365782294290
        // 344306344403172

        bool merged_any = true;

        while (merged_any)
        {
            merged_any = false;

            for (auto it = fresh_ranges.begin(); it != fresh_ranges.end();)
            {
                if (p.first <= it->second && p.second >= it->first)
                {
                    cout << "old: left: " << it->first << " right: " << it->second << endl;
                    cout << "new: left: " << p.first << " right: " << p.second << endl;

                    p.first  = min(p.first, it->first);
                    p.second = max(p.second, it->second);

                    cout << "merged: left: " << p.first << " right: " << p.second << endl;

                    it         = fresh_ranges.erase(it);
                    merged_any = true;
                }
                else
                {
                    ++it;
                }
            }
        }

        fresh_ranges.push_back(p);
    }

    for (auto fresh_range : fresh_ranges)
    {
        result += fresh_range.second - fresh_range.first + 1;
    }
    // vector<int64_t> ingredients;
    // while (getline(in, line))
    // {
    //     if (line.empty())
    //     {
    //         cout << "Found empty line" << endl;
    //         continue;
    //     }
    //     ingredients.push_back(stoll(line));
    // }
    //
    // for (int64_t ingredient : ingredients)
    // {
    //     for (auto fresh_range : fresh_ranges)
    //     {
    //         if (ingredient >= fresh_range.first && ingredient <= fresh_range.second)
    //         {
    //             result++;
    //             break;
    //         }
    //     }
    // }
    cout << "Result: " << result << endl;
}
