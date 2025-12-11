#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

using namespace std;

int main()
{
    cout << "Day 7 Part 1" << endl;
    ifstream in("input-test.txt");
    if (!in)
    {
        cerr << "No input file found" << endl;
        return 1;
    }
    vector<string> lines;
    string line;
    while (getline(in, line))
    {
        if (line.empty())
        {
            continue;
        }
        lines.push_back(line);
    }

    for (auto line : lines)
        cout << line << endl;

    pair<size_t, size_t> s_index(0, 0);

    for (size_t y = 0; y < lines.size(); ++y)
    {
        for (size_t x = 0; x < lines.at(0).size(); ++x)
        {
            size_t chr = lines.at(y).at(x);
            if (chr == 'S')
            {
                s_index.first  = y;
                s_index.second = x;
                break;
            }
        }
    }

    cout << "S : x " << s_index.second << " y " << s_index.first << endl;

    vector<pair<size_t, size_t>> beams;
    vector<vector<pair<size_t, size_t>>> all_beams;

    pair<size_t, size_t> first_beam(s_index.first + 1, s_index.second);
    beams.push_back(first_beam);
    all_beams.push_back(beams);
    int64_t result = 0;

    while (beams.at(0).first + 1 < lines.size())
    {
        vector<pair<size_t, size_t>> next_beams;
        for (auto beam : beams)
        {
            char empty_or_split = lines.at(beam.first + 1).at(beam.second);
            if (empty_or_split == '^')
            {
                result++;
                auto next_beam_left  = beam;
                auto next_beam_right = beam;
                next_beam_left.first += 2;
                next_beam_right.first += 2;
                --next_beam_left.second;
                ++next_beam_right.second;
                if (next_beams.empty())
                {
                    next_beams.push_back(next_beam_left);
                }
                else if (next_beams.back().second != next_beam_left.second)
                {
                    next_beams.push_back(next_beam_left);
                }
                next_beams.push_back(next_beam_right);
            }
            else
            {
                auto next_beam = beam;
                next_beam.first += 2;
                if (next_beams.empty())
                {
                    next_beams.push_back(next_beam);
                }
                else if (next_beams.back().second != next_beam.second)
                {
                    next_beams.push_back(next_beam);
                }
            }
        }
        beams = next_beams;
        all_beams.push_back(beams);
    }

    // Draw beams
    for (auto beamss : all_beams)
    {
        for (auto beam : beamss)
        {
            lines.at(beam.first).at(beam.second)     = '|';
            lines.at(beam.first - 1).at(beam.second) = '|';
        }
    }
    cout << result << endl;
    cout << result << endl;
    float test = 0;
    for (auto line : lines)
    {
        test += 0.5;
        cout << (int)test << "  ";
        cout << line << endl;
    }

    for (auto beamss : all_beams)
    {
    }
}
