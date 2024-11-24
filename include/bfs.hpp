#ifndef BPS_HPP
#define BFS_HPP

#include <utility>
#include <vector>

typedef long long ll;

typedef unsigned long long ull;

using namespace std;

pair<double, vector<pair<ull, ull>>> bfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2);

#endif