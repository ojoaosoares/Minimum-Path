#include "dijkstra.hpp"
#include "heap.hpp"
#include <algorithm>
#include "map.hpp"

pair<results, vector<pair<ull, ull>>> dijkstra(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {

    ull rows = map.size(), cols = map[0].size();

    Map_Hash_Custom hash(rows, cols); Comp_Dijkstra comp;

    Heap<pair<ull, ull>, double, Comp_Dijkstra, Map_Hash_Custom> priority_queue(rows*cols, comp, hash);

    results result = {0, 0};

    pair<ull, ull> key(y1, x1); 
    double distance = 0;
    
    priority_queue.insert(key, distance);

    vector<vector<pair<ull,ull>>> path(rows, vector<pair<ull, ull>>(cols, pair<ull, ull>(0, 0)));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    path[y1][x1] = pair<ull, ull>(y1 + 1, x1 + 1);
    visited[y1][x1] = true;

    while (!priority_queue.empty())
    {
        pair<pair<ull, ull>, double> keyAndValue = priority_queue.remove();
        result.nodesExpanded++;

        key = keyAndValue.first;

        if (key.first == y2 && key.second == x2)
        {
            result.distance = keyAndValue.second;
            break;
        }

        visited[key.first][key.second] = true;

        vector<pair<ull, ull>> explore = sucessorFunction(key.second, key.first, map);

        for (pair<ull, ull> newKey : explore)
        {
            if (!visited[newKey.first][newKey.second])
            {
                distance = keyAndValue.second + terrain_types[map[newKey.first][newKey.second]];

                pair<pair<ull, ull>, double> *exist = priority_queue.contains(newKey);

                if (exist == nullptr)
                {
                    priority_queue.insert(newKey, distance);
                    path[newKey.first][newKey.second] = pair<ull, ull>(key.first + 1, key.second + 1);
                }
                
                else if (distance < exist->second)
                {
                    priority_queue.update(newKey, distance);
                    path[newKey.first][newKey.second] = pair<ull, ull>(key.first + 1, key.second + 1);
                }
            }
        }
    }

    ull currX = x2, currY = y2;

    vector<pair<ull, ull>> finalPath;

    if (!path[currY][currX].first && !path[currY][currX].second)
    {
        result.distance = -1;
        return pair<results, vector<pair<ull, ull>>>(result, finalPath);   
    }

    while (path[currY][currX].first != currY + 1 || path[currY][currX].second != currX + 1)
    {
        finalPath.push_back(pair<ull, ull>(currX, currY));

        ull tempY = path[currY][currX].first - 1,
        tempX = path[currY][currX].second - 1;

        currY = tempY; currX = tempX;
    }

    finalPath.push_back(pair<ull, ull>(currX, currY));

    reverse(finalPath.begin(), finalPath.end());
    
    return pair<results, vector<pair<ull, ull>>>(result, finalPath);   
}
