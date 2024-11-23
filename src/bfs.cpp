#include "bfs.hpp"
#include <queue>
#include <stack>
#include "map.hpp"

pair<double, vector<pair<ull, ull>>> bfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {
    // Input: (Graph_Ad_List) Graph, (int) the start vertice
    // Complexity: O(V + E)
    // Output: (bool) true if all vertices were reached, (vector) a vector containg all vertices predecessors, (int) the fullDistance

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
            
            while(!vertexQueue.empty())
            {
                pair<ull, ull> coor = vertexQueue.front();
                vertexQueue.pop();

                coor.first--; coor.second--;
                // To follow the matrix index

                if (coor.first > 0)
                    if (map[coor.first - 1][coor.second] != WALL && !path[coor.first - 1][coor.second].first && !path[coor.first - 1][coor.second].second) {

                        path[coor.first - 1][coor.second] = pair<ull, ull>(coor.first + 1, coor.second + 1);

                        if (coor.first - 1 + 1 == y2 && coor.second + 1 == x2)
                        {
                            found = true;
                            break;
                        }

                        vertexQueue.push(pair<ull, ull>(coor.first - 1 + 1, coor.second + 1));
                    }
                        
                    
                if (coor.first + 1 < rows)
                    if (map[coor.first + 1][coor.second] != WALL && !path[coor.first + 1][coor.second].first && !path[coor.first + 1][coor.second].second)
                    {
                        path[coor.first + 1][coor.second] = pair<ull, ull>(coor.first + 1, coor.second + 1);

                        if (coor.first + 1 + 1 == y2 && coor.second + 1 == x2)
                        {
                            found = true;
                            break;
                        }

                        vertexQueue.push(pair<ull, ull>(coor.first + 1 + 1, coor.second + 1));
                    }

                if (coor.second > 0)
                    if (map[coor.first][coor.second - 1] != WALL && !path[coor.first][coor.second - 1].first && !path[coor.first][coor.second - 1].second)
                    {
                        path[coor.first][coor.second - 1] = pair<ull, ull>(coor.first + 1, coor.second + 1);

                        if (coor.first + 1 == y2 && coor.second - 1 + 1 == x2)
                        {
                            found = true;
                            break;
                        }

                        vertexQueue.push(pair<ull, ull>(coor.first + 1, coor.second - 1 + 1));
                    }

                if (coor.second + 1 < cols)
                    if (map[coor.first][coor.second + 1] != WALL && !path[coor.first][coor.second + 1].first && !path[coor.first][coor.second + 1].second)
                    {
                        path[coor.first][coor.second + 1] = pair<ull, ull>(coor.first + 1, coor.second + 1);

                        if (coor.first + 1 == y2 && coor.second + 1 + 1 == x2)
                        {
                            found = true;
                            break;
                        }

                        vertexQueue.push(pair<ull, ull>(coor.first + 1, coor.second + 1 + 1));
                    }
            }

            if (found) break;

            // layer++;
        }
    }

    ull curX = x2, curY = y2;

    double pathSize = 0;

    vector<pair<ull, ull>> finalPath;

    stack<pair<ull, ull>> pathAux;

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

        pathAux.push(pair<ull, ull>(curX, curY));

        curY = path[curY - 1][curX - 1].first;
        curX = path[curY - 1][curX - 1].second;
    }

    pathAux.push(pair<ull, ull>(curX, curY));

    while (!pathAux.empty())
    {
        pair<ull, ull> coor = pathAux.top();
        pathAux.pop();

        finalPath.push_back(coor);
    }
    
    
    return pair<double, vector<pair<ull, ull>>>(pathSize, finalPath);    
}
