#include "map.hpp"

unordered_map<char, double> terrain_types = {
    {GRASS, GRASS_VALUE},
    {HIGH_GRASS, HIGH_GRASS_VALUE},
    {WATER, WATER_VALUE},
    {FIRE, FIRE_VALUE}
};

vector<vector<char>> readMap(const string &filename) {
    ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Could not open the file: " + filename);

    size_t rows, cols;

    file >> cols >> rows;

    vector<vector<char>> map(rows, vector<char>(cols));

    for (size_t r = 0; r < rows; r++)
        for (size_t c = 0; c < cols; c++)
            file >> map[r][c];

    file.close();
    
    return map;
}