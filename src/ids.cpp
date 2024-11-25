#include "ids.hpp"
#include "dfs.hpp"
#include "heuristic.hpp"
#include <limits>

pair<double, vector<pair<ull, ull>>> ids(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2)
{
    pair<double, vector<pair<ull, ull>>> sizeAndPath;

    ull minimumDepth = (ull) manhattanHeuristic(x1, y1, x2, y2);

    for (size_t i = minimumDepth; i < numeric_limits<ull>::max(); i++)
    {    
        sizeAndPath = dfs(map, x1, y1, x2, y2, i);

        if (sizeAndPath.first != -1)
            return sizeAndPath;
    }

    return sizeAndPath;
}
