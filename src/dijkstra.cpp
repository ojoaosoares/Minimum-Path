#include "dijkstra.hpp"
#include "heap.hpp"
#include <algorithm>
#include "map.hpp"

pair<double, vector<pair<ull, ull>>> dijkstra(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {
    
    if (map[y1-1][x1-1] == WALL || map[y2-1][x2-1] == WALL)
        throw invalid_argument("Coordinates invalid");

    ull rows = map.size(), cols = map[0].size();

    Map_Hash_Custom hash(rows, cols); Comp_Dijkstra comp;

    Heap<pair<ull, ull>, double, Comp_Dijkstra, Map_Hash_Custom> priority_queue(rows*cols, comp, hash);

    pair<ull, ull> key(y1, x1); double distance = 0;
    priority_queue.insert(key, distance);

    vector<vector<pair<ull,ull>>> path(rows, vector<pair<ull, ull>>(cols, pair<ull, ull>(0, 0)));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    path[y1 - 1][x1 - 1] = pair<ull, ull>(y1, x1);
    visited[y1 - 1][x1 - 1] = true;

    while (!priority_queue.empty())
    {
        pair<pair<ull, ull>, double> curr_vertice = priority_queue.remove();

        pair<ull, ull> coor = curr_vertice.first;

        if (coor.first == y2 && coor.second == x2)
        {
            distance = curr_vertice.second;
            break;
        }

        coor.first--; coor.second--; // To follow the matrix index

        visited[coor.first][coor.second] = true;

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
            if (map[exCoor.first][exCoor.second] != WALL && !visited[exCoor.first][exCoor.second])
            {
                distance = curr_vertice.second; // update distance

                switch (map[exCoor.first][exCoor.second])
                {
                    case GRASS:
                        distance += GRASS_VALUE;
                        break;  
                    case HIGH_GRASS:
                        distance += HIGH_GRASS_VALUE;
                        break;
                    case WATER:
                        distance += WATER_VALUE;
                        break;
                    case FIRE:
                        distance += FIRE_VALUE;
                        break;
                    default:
                        break;
                }

                pair<ull, ull> key = {exCoor.first + 1, exCoor.second + 1};

                pair<pair<ull, ull>, double> *exist = priority_queue.contains(key);

                if (exist == nullptr)
                {
                    priority_queue.insert(key, distance);
                    path[exCoor.first][exCoor.second] = pair<ull, ull>(coor.first + 1, coor.second + 1);
                }
                
                else if (distance < exist->second)
                {
                    priority_queue.update(key, distance);
                    path[exCoor.first][exCoor.second] = pair<ull, ull>(coor.first + 1, coor.second + 1);
                }
            }
        }
    }

    ull curX = x2, curY = y2;

    vector<pair<ull, ull>> finalPath;

    if (!path[curY - 1][curX - 1].first && !path[curY - 1][curX - 1].second)
        return pair<double, vector<pair<ull, ull>>>(-1, finalPath);   

    while (path[curY - 1][curX - 1].first != curY || path[curY - 1][curX - 1].second != curX)
    {
        finalPath.push_back(pair<ull, ull>(curX, curY));

        ull tempY = path[curY - 1][curX - 1].first,
        tempX = path[curY - 1][curX - 1].second;

        curY = tempY; curX = tempX;
    }

    finalPath.push_back(pair<ull, ull>(curX, curY));

    reverse(finalPath.begin(), finalPath.end());
    
    return pair<double, vector<pair<ull, ull>>>(distance, finalPath);   
}
