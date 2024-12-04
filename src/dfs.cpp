#include "dfs.hpp"
#include "map.hpp"
#include <algorithm>

pair<results, vector<pair<ull, ull>>> dfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, ull maxDepth) {
    // Input: (Matrix) Map, (int) x1, y1 start coordinates, x2, y2 end coordinates 
    // Time Complexity: O(b^m) m is the maximum solution size or the limited depth
    // Space Complexity: O(m*b)
    // Complete: No
    // Optimal: No
    // Output: results, vector<pair<int, int>> path

    ull rows = map.size(), cols = map[0].size();

    vector<vector<ull>> visited(rows, vector<ull>(cols, 0)); 
    visited[y1][x1] = maxDepth;

    results result = {0, 0};

    vector<pair<ull, ull>> finalPath; 

    if (!recdfs(map, x1, y1, x2, y2, visited, result, finalPath, maxDepth))
    {
        result.distance = -1;
        return pair<results, vector<pair<ull, ull>>>(result, finalPath);   
    }

    finalPath.push_back(pair<ull, ull>(x1, y1));

    reverse(finalPath.begin(), finalPath.end());
    
    return pair<results, vector<pair<ull, ull>>>(result, finalPath);    
}

bool recdfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, vector<vector<ull>> &visited, results &result, vector<pair<ull,ull>> &finalPath, ull maxDepth) {
    // Input: (Graph_Ad_List) Graph, (int) the start vertice, (vector) a boolean vector that tells if a vertex was already visited, (list) a list ordered by who has the greatest finish time

    result.nodesExpanded++;

    pair<ull, ull> key = {y1, x1};

    if (key.first == y2 && key.second == x2) 
        return true;

    if (maxDepth)
    {    
        vector<pair<ull, ull>> explore = sucessorFunction(key.second, key.first, map);
        
        for (pair<ull, ull> newKey : explore)
        {
            if (maxDepth - 1 > visited[newKey.first][newKey.second]) {

                visited[newKey.first][newKey.second] = maxDepth - 1;

                if (recdfs(map, newKey.second, newKey.first, x2, y2, visited, result, finalPath, maxDepth - 1))
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