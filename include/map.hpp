#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

typedef long long ll;

typedef unsigned long long ull;

#define GRASS '.'
#define GRASS_VALUE 1.0
#define HIGH_GRASS ';'
#define HIGH_GRASS_VALUE 1.5
#define WATER '+'
#define WATER_VALUE 2.5
#define FIRE 'x'
#define FIRE_VALUE 6.0
#define WALL '@'

extern unordered_map<char, double> terrain_types;

vector<vector<char>> readMap(const string &filename);

vector<pair<ull, ull>> sucessorFunction(ull x, ull y, const vector<vector<char>> &map);

#endif