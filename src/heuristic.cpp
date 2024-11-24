#include "heuristic.hpp"
#include <cmath> 

double manhattanHeuristic(ull x1, ull y1, ull x2, ull y2) {

    return fabs((double) x2 - (double) x1) + fabs((double) y2 - (double) y1);
}