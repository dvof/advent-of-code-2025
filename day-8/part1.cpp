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
    size_t new_id,
    size_t node,
    unordered_map<size_t, pair<size_t, set<size_t>>>& circuits,
    unordered_set<size_t>& visited)
{
    if (!visited.insert(node).second)
        return;

    auto it = circuits.find(node);
    if (it == circuits.end())
        return;

    it->second.first = new_id;

    for (auto nxt : it->second.second)
        overwriteId(new_id, nxt, circuits, visited);
}

size_t circuitSizeFromMarking(
    size_t start,
    const unordered_map<size_t, pair<size_t, set<size_t>>>& circuits,
    unordered_set<size_t>& globalVisited)
{
    vector<size_t> stack;
    stack.push_back(start);
    size_t count = 0;

    while (!stack.empty())
    {
        size_t node = stack.back();
        stack.pop_back();

        if (!globalVisited.insert(node).second)
            continue;

        ++count;

        auto it = circuits.find(node);
        if (it == circuits.end())
            continue;

        for (size_t nxt : it->second.second)
            stack.push_back(nxt);
    }
    return count;
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

            unordered_set<size_t> visited;
            overwriteId(i_id, closest_p_index, circuits, visited);

            id_and_connected->second.second.insert(closest_p_index);
            id_and_connected_closest->second.second.insert(i);
        }
    }

    vector<int> sizes;
    unordered_set<size_t> globalVisited;

    for (auto& [idx, _] : circuits)
    {
        if (globalVisited.count(idx))
            continue;
        sizes.push_back((int)circuitSizeFromMarking(idx, circuits, globalVisited));
    }
    sort(sizes.rbegin(), sizes.rend());
    for (int s : sizes)
        cout << s << "\n";
    cout << "Result" << endl << sizes[0] * sizes[1] * sizes[2] << endl;
}
