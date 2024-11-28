#include "bfs.hpp"
#include <queue>
#include <algorithm>
#include "map.hpp"

pair<results, vector<pair<ull, ull>>> bfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {
    // Input: (Matrix) Map, (int) x1, y1 start coordinates, x2, y2 end coordinates 
    // Time Complexity: O(b^d) // d is the shortest solution size
    // Space Complexity: O(b^d)
    // Complete: yes
    // Optimal: Yes, if the cost of all steps are uniform
    // Output: results, vector<pair<int, int>> path

    ull rows = map.size(), cols = map[0].size();

    queue<pair<ll, ll>> vertexQueue;

    results result = {0, 0};

    vertexQueue.push(pair<ll, ll>(y1, x1));

    vector<vector<pair<ull,ull>>> path(rows, vector<pair<ull, ull>>(cols, pair<ull, ull>(0, 0)));

    path[y1][x1] = pair<ull, ull>(y1 + 1, x1 + 1);

    if (y1 != y2 || x1 != x2)
    {
        while (!vertexQueue.empty())
        {
            bool found = false;
            vector<pair<ull, ull>> layerVertices;

            while(!vertexQueue.empty())
            {
                layerVertices.push_back(vertexQueue.front());
                vertexQueue.pop();
            }
            
            for (pair<ull, ull> &key : layerVertices)
            {
                result.nodesExpanded++;

                vector<pair<ull, ull>> explore = sucessorFunction(key.second, key.first, map);

                for (pair<ull, ull> newKey : explore)
                {
                    if (!path[newKey.first][newKey.second].first && !path[newKey.first][newKey.second].second) {

                        path[newKey.first][newKey.second] = pair<ull, ull>(key.first + 1, key.second + 1);

                        if (newKey.first == y2 && newKey.second == x2)
                        {
                            found = true;
                            break;
                        }

                        vertexQueue.push(pair<ull, ull>(newKey.first, newKey.second));
                    }
                }
            }

            if (found) break;
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
        result.distance += terrain_types[map[currY][currX]];

        finalPath.push_back(pair<ull, ull>(currX, currY));

        ull tempY = path[currY][currX].first - 1,
        tempX = path[currY][currX].second - 1;

        currY = tempY; currX = tempX;
    }

    finalPath.push_back(pair<ull, ull>(currX, currY));

    reverse(finalPath.begin(), finalPath.end());
    
    return pair<results, vector<pair<ull, ull>>>(result, finalPath); 
}
