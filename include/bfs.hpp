#ifndef BPS_HPP
#define BFS_HPP

#include <utility>
#include <vector>
#include "results.hpp"

using namespace std;

pair<results, vector<pair<ull, ull>>> bfs(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2);

#endif