#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef struct
{
    int x;
    int y;
    int z;
} Point;

size_t getClosestPoint(const vector<Point>& points, size_t index)
{
    Point comp = points.at(index);
    vector<pair<int64_t, size_t>> distances;
    for (size_t i = 0; i < points.size(); ++i)
    {
        if (i == index)
        {
            continue;
        }
        int64_t x = points.at(i).x - comp.x;
        int64_t y = points.at(i).y - comp.y;
        int64_t z = points.at(i).z - comp.z;
        distances.push_back({x * x + y * y + z * z, i});
    }
    sort(distances.begin(), distances.end());
    return distances.front().second;
}

void overwriteId(
    size_t index_in,
    size_t index_ow,
    unordered_map<size_t, pair<size_t, set<size_t>>>& circuits)
{
    auto id      = circuits.find(index_in)->second.first;
    auto find_ov = circuits.find(index_ow);

    if (find_ov == circuits.end())
    {
        return;
    }
    find_ov->second.first = index_in;
    for (auto new_index_ow : find_ov->second.second)
    {
        overwriteId(index_in, new_index_ow, circuits);
    }
    return;
}

int main()
{
    cout << "Day 8 Part 1" << endl;
    ifstream in("input-test.txt");

    if (!in)
    {
        cerr << "Error reading file" << endl;
        return 1;
    }

    // index, circuit_ID, connected indexs
    unordered_map<size_t, pair<size_t, set<size_t>>> circuits;
    // circuit id, first connected index
    unordered_map<size_t, size_t> circuit_ids;
    size_t circuit_id = 0;
    string line;
    vector<Point> points;

    while (getline(in, line))
    {
        if (line.empty())
        {
            continue;
        }
        stringstream ss(line);
        Point p;
        char comma;
        ss >> p.x >> comma >> p.y >> comma >> p.z;
        points.push_back(p);
    }
    for (auto p : points)
        cout << "p.x " << p.x << " p.y " << p.y << " p.z " << p.z << endl;

    for (size_t i = 0; i < points.size(); ++i)
    {
        size_t closest_p_index        = getClosestPoint(points, i);
        auto id_and_connected         = circuits.find(i);
        auto id_and_connected_closest = circuits.find(closest_p_index);
        if (id_and_connected == circuits.end())
        {
            if (id_and_connected_closest == circuits.end())
            {
                circuit_id++;
                circuits[closest_p_index] = {circuit_id, {i}};
                circuits[i]               = {circuit_id, {closest_p_index}};
                circuit_ids[circuit_id]   = i;
                continue;
            }
            size_t closest_id = id_and_connected_closest->second.first;
            id_and_connected_closest->second.second.insert(i);
            circuits[i] = {closest_id, {closest_p_index}};
        }
        else
        {
            size_t i_id = id_and_connected->second.first;
            if (id_and_connected_closest == circuits.end())
            {

                circuits[closest_p_index] = {i_id, {i}};
                id_and_connected->second.second.insert(closest_p_index);
                continue;
            }
            size_t closest_id = id_and_connected_closest->second.first;
            circuit_ids.erase(closest_id);
            overwriteId(i, closest_id, circuits);
            id_and_connected->second.second.insert(closest_id);
        }
    }
    vector<int> sizes;
    for (auto c_id : circuit_ids)
        sizes.push_back(circuits.find(c_id.second)->second.second.size());

    sort(sizes.begin(), sizes.end());
    for (auto size : sizes)
        cout << size << endl;
}
