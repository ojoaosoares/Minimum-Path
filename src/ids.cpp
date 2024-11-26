#include "ids.hpp"
#include "dfs.hpp"
#include "heuristic.hpp"
#include <limits>

pair<results, vector<pair<ull, ull>>> ids(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2)
{
    pair<results, vector<pair<ull, ull>>> resultAndPath;

    results resultAcumulator = {0, 0, 0, 0};

    ull minimumDepth = (ull) manhattanHeuristic(x1, y1, x2, y2);

    for (size_t i = minimumDepth; i < numeric_limits<ull>::max(); i++)
    {    
        resultAndPath = dfs(map, x1, y1, x2, y2, i);

        resultAcumulator.nodesAnalyzed += resultAndPath.first.nodesAnalyzed;
        resultAcumulator.nodesReached += resultAndPath.first.nodesReached;
        resultAcumulator.nodesExplored += resultAndPath.first.nodesExplored;

        resultAcumulator.distance = resultAndPath.first.distance;

        resultAndPath.first = resultAcumulator;

        if (resultAndPath.first.distance != -1)
            return resultAndPath;
    }

    return resultAndPath;
}
