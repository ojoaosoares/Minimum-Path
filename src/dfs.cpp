#include "dfs.hpp"
#include "map.hpp"
#include <algorithm>

pair<double, vector<pair<ull, ull>>> dfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, ull maxDepth) {
    // Input: (Matrix) Map, (int) x1, y1 start coordinates, x2, y2 end coordinates , (int) maxDepth
    // Complexity: O(V + E)
    // Output: double path size, vector<pair<int, int>> path

    if (map[y1][x1] == WALL || map[y2][x2] == WALL)
        throw invalid_argument("Coordinates invalid");

    ull rows = map.size(), cols = map[0].size();

    vector<vector<pair<ull,ull>>> path(rows, vector<pair<ull, ull>>(cols, pair<ull, ull>(0, 0)));
    path[y1][x1] = pair<ull, ull>(y1 + 1, x1 + 1);

    recdfs(map, x1, y1, x2, y2, path, 0, maxDepth);

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

bool recdfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, vector<vector<pair<ull,ull>>> &path,  ull currDepth,  ull maxDepth) {
    // Input: (Graph_Ad_List) Graph, (int) the start vertice, (vector) a boolean vector that tells if a vertex was already visited, (list) a list ordered by who has the greatest finish time
    
    ull rows = map.size(), cols = map[0].size();

    pair<ull, ull> key = {y1, x1};

    vector<pair<ull, ull>> explore;

    if (currDepth != maxDepth)
    {
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
                    return true;

                if (recdfs(map, newKey.second, newKey.first, x2, y2, path, currDepth + 1, maxDepth))
                    return true;
            }
        }   
    }

    return false;
}