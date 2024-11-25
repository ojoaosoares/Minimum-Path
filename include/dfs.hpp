#ifndef DFS_HPP
#define DFS_HPP

#include <vector>
#include <string>

typedef long long ll;

using namespace std;

#include <utility>
#include <vector>

typedef long long ll;

typedef unsigned long long ull;

using namespace std;

pair<double, vector<pair<ull, ull>>> dfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, ull maxDepth);

bool recdfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2, vector<vector<pair<ull,ull>>> &path, ull currDepth,  ull maxDepth);

#endif