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

    // ull layer = 0;

    if (y1 != y2 || x1 != x2)
    {
        // layer = 1;

        while (!vertexQueue.empty())
        {
            bool found = false;
            vector<pair<ull, ull>> layerVertices;

            while(!vertexQueue.empty())
            {
                layerVertices.push_back(vertexQueue.front());
                vertexQueue.pop();
            }
            
            for (pair<ull, ull> &coor : layerVertices)
            {
                vector<pair<ull, ull>> explore;

                if (coor.first > 0)
                    explore.push_back(pair<ull, ull>(coor.first - 1, coor.second));

                if (coor.first + 1 < rows)
                    explore.push_back(pair<ull, ull>(coor.first + 1, coor.second));

                if (coor.second > 0)
                    explore.push_back(pair<ull, ull>(coor.first, coor.second - 1));

                if (coor.second + 1 < cols)
                    explore.push_back(pair<ull, ull>(coor.first, coor.second + 1));


                for (pair<ull, ull> exCoor : explore)
                {
                    if (map[exCoor.first][exCoor.second] != WALL && !path[exCoor.first][exCoor.second].first && !path[exCoor.first][exCoor.second].second) {

                        path[exCoor.first][exCoor.second] = pair<ull, ull>(coor.first + 1, coor.second + 1);

                        if (exCoor.first == y2 && exCoor.second == x2)
                        {
                            found = true;
                            break;
                        }

                        vertexQueue.push(pair<ull, ull>(exCoor.first, exCoor.second));
                    }
                }
            }

            if (found) break;

            // layer++;
        }
    }

    ull curX = x2, curY = y2;

    double pathSize = 0;

    vector<pair<ull, ull>> finalPath;

    if (!path[curY][curX].first && !path[curY][curX].second)
        return pair<double, vector<pair<ull, ull>>>(-1, finalPath);   

    while (path[curY][curX].first != curY + 1 || path[curY][curX].second != curX + 1)
    {
        pathSize += terrain_types[map[curY][curX]];

        finalPath.push_back(pair<ull, ull>(curX, curY));

        ull tempY = path[curY][curX].first - 1,
        tempX = path[curY][curX].second - 1;

        curY = tempY; curX = tempX;
    }

    finalPath.push_back(pair<ull, ull>(curX, curY));

    reverse(finalPath.begin(), finalPath.end());
    
    return pair<double, vector<pair<ull, ull>>>(pathSize, finalPath);    
}
