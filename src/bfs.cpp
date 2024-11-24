#include "bfs.hpp"
#include <queue>
#include <algorithm>
#include "map.hpp"

pair<double, vector<pair<ull, ull>>> bfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {
    // Input: (Matrix) Map, (int) x1, y1 start coordinates, x2, y2 end coordinates 
    // Complexity: O(V + E)
    // Output: double path size, vector<pair<int, int>> path

    if (map[y1][x1] == WALL || map[y2][x2] == WALL)
        throw invalid_argument("Coordinates invalid");

    ull rows = map.size(), cols = map[0].size();

    queue<pair<ll, ll>> vertexQueue;
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
                vector<pair<ull, ull>> explore;

                if (key.first > 0) //Try to go down
                    explore.push_back(pair<ull, ull>(key.first - 1, key.second));

                if (key.first + 1 < rows) // Try to go up
                    explore.push_back(pair<ull, ull>(key.first + 1, key.second));

                if (key.second > 0) // Try to go left
                    explore.push_back(pair<ull, ull>(key.first, key.second - 1));

                if (key.second + 1 < cols) // Try to go right
                    explore.push_back(pair<ull, ull>(key.first, key.second + 1));


                for (pair<ull, ull> newKey : explore)
                {
                    if (map[newKey.first][newKey.second] != WALL && !path[newKey.first][newKey.second].first && !path[newKey.first][newKey.second].second) {

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

    double distance = 0;

    vector<pair<ull, ull>> finalPath;

    if (!path[currY][currX].first && !path[currY][currX].second)
        return pair<double, vector<pair<ull, ull>>>(-1, finalPath);   

    while (path[currY][currX].first != currY + 1 || path[currY][currX].second != currX + 1)
    {
        distance += terrain_types[map[currY][currX]];

        finalPath.push_back(pair<ull, ull>(currX, currY));

        ull tempY = path[currY][currX].first - 1,
        tempX = path[currY][currX].second - 1;

        currY = tempY; currX = tempX;
    }

    finalPath.push_back(pair<ull, ull>(currX, currY));

    reverse(finalPath.begin(), finalPath.end());
    
    return pair<double, vector<pair<ull, ull>>>(distance, finalPath);    
}
