#include "dfs.hpp"
#include "map.hpp"
#include <algorithm>

pair<results, vector<pair<ull, ull>>> dfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, ull maxDepth) {
    // Input: (Matrix) Map, (int) x1, y1 start coordinates, x2, y2 end coordinates , (int) maxDepth
    // Complexity: O(V + E)
    // Output: double path size, vector<pair<int, int>> path

    ull rows = map.size(), cols = map[0].size();

    vector<vector<pair<ull,ull>>> path(rows, vector<pair<ull, ull>>(cols, pair<ull, ull>(0, 0)));
    path[y1][x1] = pair<ull, ull>(y1 + 1, x1 + 1);

    results result = {0, 0, 0, 0};
    result.nodesReached++; result.nodesAnalyzed++;

    vector<pair<ull, ull>> finalPath; 

    if (!recdfs(map, x1, y1, x2, y2, path, result, finalPath, 0, maxDepth))
    {
        result.distance = -1;
        return pair<results, vector<pair<ull, ull>>>(result, finalPath);   
    }

    finalPath.push_back(pair<ull, ull>(x1, y1));

    reverse(finalPath.begin(), finalPath.end());
    
    return pair<results, vector<pair<ull, ull>>>(result, finalPath);    
}

bool recdfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, vector<vector<pair<ull,ull>>> &path, results &result, vector<pair<ull,ull>> &finalPath, ull currDepth,  ull maxDepth) {
    // Input: (Graph_Ad_List) Graph, (int) the start vertice, (vector) a boolean vector that tells if a vertex was already visited, (list) a list ordered by who has the greatest finish time
    
    ull rows = map.size(), cols = map[0].size();

    result.nodesExplored++;

    pair<ull, ull> key = {y1, x1};

    if (currDepth != maxDepth)
    {
        vector<pair<ull, ull>> explore = sucessorFunction(key.second, key.first, map);

        for (pair<ull, ull> newKey : explore)
        {
            if (!path[newKey.first][newKey.second].first && !path[newKey.first][newKey.second].second) {

                path[newKey.first][newKey.second] = pair<ull, ull>(key.first + 1, key.second + 1);

                result.nodesReached++; result.nodesAnalyzed++;

                if (newKey.first == y2 && newKey.second == x2)
                {
                    result.distance = terrain_types[map[newKey.first][newKey.second]];
                    finalPath.push_back(pair<ull, ull>(newKey.second, newKey.first));
                    return true;
                }

                if (recdfs(map, newKey.second, newKey.first, x2, y2, path, result, finalPath, currDepth + 1, maxDepth))
                {
                    result.distance += terrain_types[map[newKey.first][newKey.second]];
                    finalPath.push_back(pair<ull, ull>(newKey.second, newKey.first));
                    return true;
                }
            }
        }   
    }

    return false;
}