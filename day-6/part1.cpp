#include <iostream>
#include <sstream>
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
        cerr << "No input file found" << endl;
        return 1;
    }

    vector<vector<int64_t>> rows_nums;
    string line;

    for (int i = 0; i < 4; ++i)
    {
        if (!getline(in, line))
        {
            cerr << "Reached end of file too early" << endl;
            return 1;
        }
        if (line.empty())
        {
            cout << "Found empty line" << endl;
            break;
        }
        istringstream iss(line);
        int64_t x;
        vector<int64_t> v;
        while (iss >> x)
        {
            v.push_back(x);
        }

        rows_nums.push_back(v);

        cout << v.size() << endl;
    }

    if (!getline(in, line))
    {
        cerr << "Reached end of file too early" << endl;
        return 1;
    }
    if (line.empty())
    {
        cout << "Found empty line" << endl;
        return 1;
    }
    vector<char> ops;
    istringstream iss(line);
    char x;
    while (iss >> x)
    {
        ops.push_back(x);
    }

    // cout << ops.size() << endl;
    // cout << ops.front() << endl;
    // cout << ops.at(2) << endl;
    // cout << ops.back() << endl;
    int64_t result = 0;

    for (size_t i = 0; i < ops.size(); ++i)
    {
        int64_t col = rows_nums.at(0).at(i);
        for (size_t j = 1; j < rows_nums.size(); ++j)
        {
            if (ops.at(i) == '+')
            {
                col += rows_nums.at(j).at(i);
            }
            else if (ops.at(i) == '*')
            {
                col *= rows_nums.at(j).at(i);
            }
        }
        result += col;
    }
    cout << result << endl;
}
