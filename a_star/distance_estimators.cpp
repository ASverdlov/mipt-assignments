#include <vector>
#include <cmath>

#include "distance_estimators.h"

using std::abs;
using std::vector;

int manhattanLOrCDistanceEstimator(const Grid& grid, 
                                   const vector<int>& supposedX, 
                                   const vector<int>& supposedY)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int sx = supposedX[grid.at(x, y)];
                int sy = supposedY[grid.at(x, y)];
                distance += abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y));
                distance += (sx != static_cast<int>(x)) || (sy != static_cast<int>(y));
            }
        }
    }
    return distance;
}

int manhattanLAndCDistanceEstimator(const Grid& grid,
                                    const vector<int>& supposedX, 
                                    const vector<int>& supposedY)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int sx = supposedX[grid.at(x, y)];
                int sy = supposedY[grid.at(x, y)];
                distance += abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y));
                distance += (sx != static_cast<int>(x)) && (sy != static_cast<int>(y));
            }
        }
    }
    return distance;
}

int manhattanDistanceEstimator(const Grid& grid,
                               const vector<int>& supposedX, 
                               const vector<int>& supposedY)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int sx = supposedX[grid.at(x, y)];
                int sy = supposedY[grid.at(x, y)];
                distance += abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y));
            }
        }
    }
    return distance;
}
