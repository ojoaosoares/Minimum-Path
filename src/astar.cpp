#include "astar.hpp"
#include "heap.hpp"
#include "map.hpp"
#include "heuristic.hpp"
#include <algorithm>

pair<results, vector<pair<ull, ull>>> astar(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {
    
    if (map[y1][x1] == WALL || map[y2][x2] == WALL)
        throw invalid_argument("Coordinates invalid");

    ull rows = map.size(), cols = map[0].size();

    Map_Hash_Custom hash(rows, cols); Comp_A_Star comp;

    Heap<pair<ull, ull>, pair<double, double>, Comp_A_Star, Map_Hash_Custom> priority_queue(rows*cols, comp, hash);

    results result = {0, 0, 0, 0};

    pair<ull, ull> key(y1, x1);
    pair<double, double> distAndHeuristic;

    distAndHeuristic.first = 0;
    distAndHeuristic.second =  manhattanHeuristic(x1, y1, x2, y2);
    
    priority_queue.insert(key, distAndHeuristic);
    result.nodesReached++; result.nodesAnalyzed++;

    vector<vector<pair<ull,ull>>> path(rows, vector<pair<ull, ull>>(cols, pair<ull, ull>(0, 0)));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    path[y1][x1] = pair<ull, ull>(y1 + 1, x1 + 1);
    visited[y1][x1] = true;

    while (!priority_queue.empty())
    {
        pair<pair<ull, ull>, pair<double, double>> keyAndValue = priority_queue.remove();
        result.nodesExplored++;

        key = keyAndValue.first;

        if (key.first == y2 && key.second == x2)
        {
            result.distance = keyAndValue.second.first;
            break;
        }

        visited[key.first][key.second] = true;

        vector<pair<ull, ull>> explore;

        if (key.first > 0)
            explore.push_back(pair<ull, ull>(key.first - 1, key.second));

        if (key.first + 1 < rows)
            explore.push_back(pair<ull, ull>(key.first + 1, key.second));

        if (key.second > 0)
            explore.push_back(pair<ull, ull>(key.first, key.second - 1));

        if (key.second + 1 < cols)
            explore.push_back(pair<ull, ull>(key.first, key.second + 1));

        for (pair<ull, ull> newKey : explore)
        {
            if (map[newKey.first][newKey.second] != WALL && !visited[newKey.first][newKey.second])
            {
                distAndHeuristic.first = keyAndValue.second.first + terrain_types[map[newKey.first][newKey.second]];

                distAndHeuristic.second = manhattanHeuristic(newKey.second, newKey.first, x2, y2);

                pair<pair<ull, ull>, pair<double, double>> *exist = priority_queue.contains(newKey);

                if (exist == nullptr)
                {
                    priority_queue.insert(newKey, distAndHeuristic);
                    path[newKey.first][newKey.second] = pair<ull, ull>(key.first + 1, key.second + 1);
                    result.nodesReached++; result.nodesAnalyzed++;
                }
                
                else if (distAndHeuristic.first < exist->second.first)
                {
                    priority_queue.update(newKey, distAndHeuristic);
                    path[newKey.first][newKey.second] = pair<ull, ull>(key.first + 1, key.second + 1);
                    result.nodesAnalyzed++;
                }
            }
        }
    }

    ull curX = x2, curY = y2;

    vector<pair<ull, ull>> finalPath;

    if (!path[curY][curX].first && !path[curY][curX].second)
    {
        result.distance = -1;
        return pair<results, vector<pair<ull, ull>>>(result, finalPath);  
    }

    while (path[curY][curX].first != curY + 1 || path[curY][curX].second != curX + 1)
    {
        finalPath.push_back(pair<ull, ull>(curX, curY));

        ull tempY = path[curY][curX].first - 1,
        tempX = path[curY][curX].second - 1;

        curY = tempY; curX = tempX;
    }

    finalPath.push_back(pair<ull, ull>(curX, curY));

    reverse(finalPath.begin(), finalPath.end());
    
    return pair<results, vector<pair<ull, ull>>>(result, finalPath);
}