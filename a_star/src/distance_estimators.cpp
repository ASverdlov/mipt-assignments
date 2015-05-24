#include <vector>
#include <cmath>

#include "distance_estimators.h"

using std::abs;
using std::vector;

int linearConflictDistanceEstimator(const Grid& grid, 
                                   const vector<int>& supposedX, 
                                   const vector<int>& supposedY)
{
    int distance = 0;
    for (size_t x1 = 0; x1 < grid.size(); ++x1) {
        for (size_t y1 = 0; y1 < grid.size(); ++y1) {
            int val1 = grid.at(x1, y1);
            int sx1 = static_cast<int>(supposedX[val1]);
            int sy1 = static_cast<int>(supposedY[val1]);
            distance += abs(sx1 - static_cast<int>(x1)) + abs(sy1 - static_cast<int>(y1));

            for (size_t x2 = 0; x2 < grid.size(); ++x2) {
                for (size_t y2 = 0; y2 < grid.size(); ++y2) {
                    int val2 = grid.at(x2, y2);
                    int sx2 = static_cast<int>(supposedX[val2]);
                    int sy2 = static_cast<int>(supposedY[val2]);
                    if (val1 == 0 || val2 == 0) {
                        continue;
                    }
                    if (x1 == x2 && x1 == sx1 && sx1 == sx2 && ((y1 < y2) != (sy1 < sy2))) {
                        ++distance;
                    }
                    if (y1 == y2 && y2 == sy1 && sy1 == sy2 && ((x1 < x2) != (sx1 < sx2))) {
                        ++distance;
                    }
                }
            }
        }
    }
    return distance / 2;
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

int misplacedTilesDistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               )
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int sx = supposedX[grid.at(x, y)];
                int sy = supposedY[grid.at(x, y)];
                distance += (sx != x) || (sy != y);
                distance += abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y));
            }
        }
    }
    return distance;

}


int nMaxSwapDistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               )
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

int strange8DistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               )
{
    int distance = 0;
    for (size_t x1 = 0; x1 < grid.size(); ++x1) {
        for (size_t y1 = 0; y1 < grid.size(); ++y1) {
            int val1 = grid.at(x1, y1);
            int sx1 = static_cast<int>(supposedX[val1]);
            int sy1 = static_cast<int>(supposedY[val1]);
            distance += 8 * (abs(sx1 - static_cast<int>(x1)) + abs(sy1 - static_cast<int>(y1)));
        }
    }
    return distance;
}

int strange16DistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               )
{
    int distance = 0;
    for (size_t x1 = 0; x1 < grid.size(); ++x1) {
        for (size_t y1 = 0; y1 < grid.size(); ++y1) {
            int val1 = grid.at(x1, y1);
            int sx1 = static_cast<int>(supposedX[val1]);
            int sy1 = static_cast<int>(supposedY[val1]);
            distance += 16 * (abs(sx1 - static_cast<int>(x1)) + abs(sy1 - static_cast<int>(y1)));
        }
    }
    return distance;
}

int strange32DistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               )
{
    int distance = 0;
    for (size_t x1 = 0; x1 < grid.size(); ++x1) {
        for (size_t y1 = 0; y1 < grid.size(); ++y1) {
            int val1 = grid.at(x1, y1);
            int sx1 = static_cast<int>(supposedX[val1]);
            int sy1 = static_cast<int>(supposedY[val1]);
            distance += 32 * (abs(sx1 - static_cast<int>(x1)) + abs(sy1 - static_cast<int>(y1)));
        }
    }
    return distance;
}
