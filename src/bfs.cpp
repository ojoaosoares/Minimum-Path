#include "bfs.hpp"
#include <queue>
#include <algorithm>
#include "map.hpp"

pair<double, vector<pair<ull, ull>>> bfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {
    // Input: (Matrix) Map, (int) x1, y1 start coordinates, x2, y2 end coordinates 
    // Complexity: O(V + E)
    // Output: double path size, vector<pair<int, int>> path

    if (map[y1-1][x1-1] == WALL || map[y2-1][x2-1] == WALL)
        throw invalid_argument("Coordinates invalid");

    ull rows = map.size(), cols = map[0].size();

    queue<pair<ll, ll>> vertexQueue;
    vertexQueue.push(pair<ll, ll>(y1, x1));

    vector<vector<pair<ull,ull>>> path(rows, vector<pair<ull, ull>>(cols, pair<ull, ull>(0, 0)));

    path[y1 - 1][x1 - 1] = pair<ull, ull>(y1, x1);

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
                coor.first--; coor.second--;
                // To follow the matrix index

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

                        if (exCoor.first + 1 == y2 && exCoor.second + 1 == x2)
                        {
                            found = true;
                            break;
                        }

                        vertexQueue.push(pair<ull, ull>(exCoor.first +  1, exCoor.second + 1));
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

    while (path[curY - 1][curX - 1].first != curY || path[curY - 1][curX - 1].second != curX)
    {
        switch (map[curY - 1][curX - 1])
        {
            case GRASS:
                pathSize += GRASS_VALUE;
                break;  
            case HIGH_GRASS:
                pathSize += HIGH_GRASS_VALUE;
                break;
            case WATER:
                pathSize += WATER_VALUE;
                break;
            case FIRE:
                pathSize += FIRE_VALUE;
                break;
            default:
                break;
        }

        finalPath.push_back(pair<ull, ull>(curX, curY));

        curY = path[curY - 1][curX - 1].first;
        curX = path[curY - 1][curX - 1].second;
    }

    finalPath.push_back(pair<ull, ull>(curX, curY));

    reverse(finalPath.begin(), finalPath.end());
    
    return pair<double, vector<pair<ull, ull>>>(pathSize, finalPath);    
}
