#include "map.hpp"

vector<vector<ll>> readMap(const string &filename) {
    ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Could not open the file: " + filename);

    ll rows, cols;

    file >> cols >> rows;

    vector<vector<ll>> map(rows, vector<ll>(cols));

    for (size_t r = 0; r < rows; r++)
        for (size_t c = 0; c < cols; c++)
            file >> map[r][c];

    return map;
}