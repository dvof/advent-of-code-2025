#include <cstdint>
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

int main()
{
    cout << "Day 7 Part 1" << endl;
    ifstream in("input.txt");
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

    // vector<pair<size_t, size_t>> beams;
    // vector<vector<pair<size_t, size_t>>> all_beams;
    // vector<pair<size_t, size_t>> descisions;
    //
    // pair<size_t, size_t> first_beam(s_index.first + 1, s_index.second);
    // beams.push_back(first_beam);
    // all_beams.push_back(beams);
    //
    // while (beams.at(0).first + 1 < lines.size())
    // {
    //     vector<pair<size_t, size_t>> next_beams;
    //     for (auto beam : beams)
    //     {
    //         char empty_or_split = lines.at(beam.first + 1).at(beam.second);
    //         if (empty_or_split == '^')
    //         {
    //             // result++;
    //             auto next_beam_left  = beam;
    //             auto next_beam_right = beam;
    //             next_beam_left.first += 2;
    //             next_beam_right.first += 2;
    //             --next_beam_left.second;
    //             ++next_beam_right.second;
    //             if (next_beams.empty())
    //             {
    //                 next_beams.push_back(next_beam_left);
    //             }
    //             else if (next_beams.back().second != next_beam_left.second)
    //             {
    //                 next_beams.push_back(next_beam_left);
    //             }
    //             next_beams.push_back(next_beam_right);
    //         }
    //         else
    //         {
    //             auto next_beam = beam;
    //             next_beam.first += 2;
    //             if (next_beams.empty())
    //             {
    //                 next_beams.push_back(next_beam);
    //             }
    //             else if (next_beams.back().second != next_beam.second)
    //             {
    //                 next_beams.push_back(next_beam);
    //             }
    //         }
    //     }
    //     beams = next_beams;
    //     all_beams.push_back(beams);
    // }
    //
    // // Draw beams
    // for (auto beamss : all_beams)
    // {
    //     for (auto beam : beamss)
    //     {
    //         lines.at(beam.first).at(beam.second)     = '|';
    //         lines.at(beam.first - 1).at(beam.second) = '|';
    //     }
    // }
    // float test = 0;
    // for (auto line : lines)
    // {
    //     test += 0.5;
    //     cout << (int)test << "  ";
    //     cout << line << endl;
    // }

    pair<size_t, size_t> cursor;
    vector<pair<size_t, size_t>> decisions;
    vector<pair<size_t, size_t>> path;

    pair<size_t, size_t> first_beam(s_index.first + 1, s_index.second);
    // decisions.push_back(first_beam);
    cursor                         = first_beam;
    bool popped                    = false;
    uint64_t result                = 0;
    lines.at(1).at(s_index.second) = '|';

    while (true)
    {
        if (cursor.first + 1 >= lines.size())
        {
            // std::cout << "End reached\n";

            result++;
            if (decisions.empty())
            {
                break;
            }
            cursor = decisions.back();
            decisions.pop_back();
            popped = true;

            // BEBUG INFO
            while (path.back().first > cursor.first)
            {
                lines.at(path.back().first).at(path.back().second)     = '.';
                lines.at(path.back().first - 1).at(path.back().second) = '.';
                path.pop_back();
            }
            path.push_back(cursor);
            // END DEBUG INFO
        }
        char empty_or_split = lines.at(cursor.first + 1).at(cursor.second);

        if (empty_or_split == '^')
        {
            // std::cout << "Split found\n";
            auto right = cursor;
            right.first += 2;
            ++right.second;

            auto left = cursor;
            left.first += 2;
            --left.second;

            if (popped)
            {
                cursor = right;
            }
            else
            {
                decisions.push_back(cursor);
                cursor = left;
            }
        }
        else
        {
            cursor.first += 2;
        }
        popped = false;

        path.push_back(cursor);
        lines.at(cursor.first).at(cursor.second)     = '|';
        lines.at(cursor.first - 1).at(cursor.second) = '|';
        for (auto line : lines)
        {
            cout << line << endl;
        }
        for (auto d : decisions)
        {
            cout << d.first;
            cout << " | ";
        }
        cout << endl;
        cout << "cursor.first: ";
        cout << cursor.first;
        cout << "  cursor.second: ";
        cout << cursor.second << endl;
        cout << result << endl;
        usleep(5 * 1000);
    }

    cout << result << endl;
}
