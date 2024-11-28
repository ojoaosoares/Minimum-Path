#include "ids.hpp"
#include "dfs.hpp"
#include "heuristic.hpp"
#include <limits>

pair<results, vector<pair<ull, ull>>> ids(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2) {
    // Input: (Matrix) Map, (int) x1, y1 start coordinates, x2, y2 end coordinates 
    // Time Complexity: O(b^d) // d is the shortest solution size
    // Space Complexity: O(d*b)
    // Complete: Yes
    // Optimal: Yes, if the cost of all steps are uniform
    // Output: results, vector<pair<int, int>> path
    pair<results, vector<pair<ull, ull>>> resultAndPath;

    results resultAcumulator = {0, 0};

    ull minimumDepth = (ull) manhattanHeuristic(x1, y1, x2, y2);

    for (size_t i = minimumDepth; i < numeric_limits<ull>::max(); i++)
    {    
        resultAndPath = dfs(map, x1, y1, x2, y2, i);
        
        resultAcumulator.nodesExpanded += resultAndPath.first.nodesExpanded;
        resultAcumulator.distance = resultAndPath.first.distance;

        resultAndPath.first = resultAcumulator;

        if (resultAndPath.first.distance != -1)
            return resultAndPath;
    }

    return resultAndPath;
}
