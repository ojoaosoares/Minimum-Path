#ifndef IDS_HPP
#define IDS_HPP

#include <utility>
#include <vector>
#include "results.hpp"

using namespace std;

pair<results, vector<pair<ull, ull>>> ids(const vector<vector<char>> &map, ull x1, ull y1, ull x2, ull y2);

#endif