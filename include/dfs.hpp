#ifndef DFS_HPP
#define DFS_HPP

#include <utility>
#include <vector>
#include <limits>

typedef long long ll;

typedef unsigned long long ull;

using namespace std;

pair<double, vector<pair<ull, ull>>> dfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, ull maxDepth = numeric_limits<ull>::max());

bool recdfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, vector<vector<pair<ull,ull>>> &path, ull currDepth,  ull maxDepth);

#endif