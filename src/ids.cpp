#include "ids.hpp"
#include "dfs.hpp"
#include "heuristic.hpp"

pair<results, vector<pair<ull, ull>>> ids(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {
    // Input: (Matrix) Map, (int) x1, y1 start coordinates, x2, y2 end coordinates 
    // Time Complexity: O(b^d) // d is the shortest solution size
    // Space Complexity: O(d*b)
    // Complete: Yes
    // Optimal: Yes, if the cost of all steps are uniform
    // Output: results, vector<pair<int, int>> path
    ull rows = map.size(), cols = map[0].size();

    pair<results, vector<pair<ull, ull>>> resultAndPath;

    ull left = (ull) manhattanHeuristic(x1, y1, x2, y2), right = cols*rows, nodesAcumulator = 0;

    for (size_t i = left; i <= right; i++)
    {    
        resultAndPath = dfs(map, x1, y1, x2, y2, i);
        
        nodesAcumulator += resultAndPath.first.nodesExpanded;

        if (resultAndPath.first.distance != -1)
            break;
    }

    resultAndPath.first.nodesExpanded = nodesAcumulator;

    return resultAndPath;
}


pair<results, vector<pair<ull, ull>>> bs_ids(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {
    // Input: (Matrix) Map, (int) x1, y1 start coordinates, x2, y2 end coordinates 
    // Time Complexity: O(b^d) // d is the shortest solution size
    // Space Complexity: O(d*b)
    // Complete: Yes
    // Optimal: Yes, if the cost of all steps are uniform
    // Output: results, vector<pair<int, int>> path
    ull rows = map.size(), cols = map[0].size();

    pair<results, vector<pair<ull, ull>>> resultAndPath;

    ull left = (ull) manhattanHeuristic(x1, y1, x2, y2), right = cols*rows, nodesAcumulator = 0;

    while (left < right) {
        ull mid = left + ((right - left) / 2);

        resultAndPath = dfs(map, x1, y1, x2, y2, mid);

        nodesAcumulator += resultAndPath.first.nodesExpanded;

        // If x greater, ignore left half
        if (resultAndPath.first.distance == -1)
            left = mid + 1;

        // If x is smaller, ignore right half
        else
            right = resultAndPath.second.size();
    }

    resultAndPath = dfs(map, x1, y1, x2, y2, left);
    nodesAcumulator += resultAndPath.first.nodesExpanded;

    resultAndPath.first.nodesExpanded = nodesAcumulator;

    return resultAndPath;
}