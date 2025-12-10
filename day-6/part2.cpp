#include <iostream>
#include <numeric>
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

    vector<string> rows_nums;
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
        rows_nums.push_back(line);
    }
    cout << rows_nums.size() << endl;

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

    cout << "Test" << endl;

    size_t col_index = 0;
    vector<int64_t> nums;
    int64_t result = 0;
    string num     = "";
    for (size_t i = 0; i < rows_nums.at(0).size(); ++i)
    {
        for (auto row : rows_nums)
        {
            num += row.at(i);
        }

        if (num.empty())
        {
            cerr << "Number is empty" << endl;
            return 1;
        }

        // All spaces
        if (num.find_first_not_of(' ') == string::npos)
        {
            char op   = ops.at(col_index);
            int64_t t = 0;
            if (op == '+')
            {
                t = accumulate(nums.begin(), nums.end(), (int64_t)0);
            }
            else if (op == '*')
            {
                t = accumulate(nums.begin(), nums.end(), (int64_t)1, multiplies<int64_t>());
            }

            result += t;
            for (auto num_i : nums)
                cout << num_i << endl;
            cout << ops.at(col_index) << endl;
            cout << t << endl;
            cout << "result" << endl;
            cout << result << endl;
            cout << endl;

            nums.clear();
            col_index++;
        }
        else
        {
            nums.push_back(stoll(num));
        }
        num = "";
    }

    char op   = ops.at(col_index);
    int64_t t = 0;
    if (op == '+')
    {
        t = accumulate(nums.begin(), nums.end(), (int64_t)0);
    }
    else if (op == '*')
    {
        t = accumulate(nums.begin(), nums.end(), (int64_t)1, multiplies<int64_t>());
    }

    result += t;
    for (auto num_i : nums)
        cout << num_i << endl;
    cout << ops.at(col_index) << endl;
    cout << t << endl;
    cout << "result" << endl;
    cout << result << endl;
    cout << endl;
}
