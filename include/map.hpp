#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

typedef long long ll;

#define GRASS '.'
#define GRASS_VALUE 1.0
#define HIGH_GRASS ':'
#define HIGH_GRASS_VALUE 1.5
#define WATER '+'
#define WATER_VALUE 2.5
#define FIRE 'x'
#define FIRE_VALUE 6.0
#define WALL '@'

vector<vector<char>> readMap(const string &filename);

#endif