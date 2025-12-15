#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <map>

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

    vector<pair<size_t, size_t>> beams;
    vector<vector<pair<size_t, size_t>>> all_beams;
    vector<vector<pair<size_t, size_t>>> all_splits;

    pair<size_t, size_t> first_beam(s_index.first + 1, s_index.second);
    beams.push_back(first_beam);
    lines.at(first_beam.first).at(first_beam.second) = '|';

    while (beams.at(0).first + 1 < lines.size())
    {
        vector<pair<size_t, size_t>> next_beams;
        vector<pair<size_t, size_t>> splits;
        for (auto beam : beams)
        {
            char empty_or_split = lines.at(beam.first + 1).at(beam.second);
            if (empty_or_split == '^')
            {
                splits.push_back({beam.first + 1, beam.second});
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
        cout << "Beam ";
        cout << beams.at(0).first << endl;
        for (auto beam : beams)
            cout << beam.second << " | ";
        cout << endl;
        cout << "Split ";
        cout << splits.at(0).first << endl;
        for (auto split : splits)
            cout << split.second << " | ";
        cout << endl;
        all_beams.push_back(beams);
        all_splits.push_back(splits);
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
    // cout << result << endl;
    for (auto line : lines)
        cout << line << endl;

    vector<map<size_t, int64_t>> splits_number_total;

    for (size_t i = all_splits.size(); i-- > 0;)
    {
        auto splits = all_splits.at(i);
        map<size_t, int64_t> splits_number;

        for (auto split : splits)
        {
            int64_t split_total    = 0;
            size_t next_left_split = split.second - 1;
            bool found             = false;
            for (auto it = splits_number_total.rbegin(); it != splits_number_total.rend(); ++it)
            {
                const auto& m = *it;
                auto f        = m.find(next_left_split);
                if (f != m.end())
                {
                    split_total += f->second;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                split_total += 1;
            }

            size_t next_right_split = split.second + 1;
            found                   = false;
            for (auto it = splits_number_total.rbegin(); it != splits_number_total.rend(); ++it)
            {
                const auto& m = *it;
                auto f        = m.find(next_right_split);
                if (f != m.end())
                {
                    split_total += f->second;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                split_total += 1;
            }
            splits_number[split.second] += split_total;
        }
        splits_number_total.push_back(splits_number);
        for (const auto& [k, v] : splits_number)
            std::cout << v << " | ";
        cout << endl;
    }
    cout << "Last split: " << splits_number_total.back().begin()->second << endl;
}
