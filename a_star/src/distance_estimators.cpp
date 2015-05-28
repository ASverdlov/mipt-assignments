#include <vector>
#include <cmath>

#include "distance_estimators.h"

using std::abs;
using std::vector;

int linearConflictDistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x1 = 0; x1 < grid.size(); ++x1) {
        for (size_t y1 = 0; y1 < grid.size(); ++y1) {
            int val1 = grid.at(x1, y1);
            int sx1 = static_cast<int>((val1 - 1) / grid.size());
            int sy1 = static_cast<int>((val1 - 1) % grid.size());
            distance += abs(sx1 - static_cast<int>(x1)) + abs(sy1 - static_cast<int>(y1));

            for (size_t x2 = 0; x2 < grid.size(); ++x2) {
                for (size_t y2 = 0; y2 < grid.size(); ++y2) {
                    int val2 = grid.at(x2, y2);
                    int sx2 = static_cast<int>((val2 - 1) / grid.size());
                    int sy2 = static_cast<int>((val2 - 1) % grid.size());
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

int manhattanLAndCDistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int sx = static_cast<int>((grid.at(x, y) - 1) / grid.size());
                int sy = static_cast<int>((grid.at(x, y) - 1) % grid.size());
                distance += abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y));
                distance += (sx != static_cast<int>(x)) && (sy != static_cast<int>(y));
            }
        }
    }
    return distance;
}

int manhattanDistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int sx = static_cast<int>((grid.at(x, y) - 1) / grid.size());
                int sy = static_cast<int>((grid.at(x, y) - 1) % grid.size());
                distance += abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y));
            }
        }
    }
    return distance;
}

int misplacedTilesDistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int sx = static_cast<int>((grid.at(x, y) - 1) / grid.size());
                int sy = static_cast<int>((grid.at(x, y) - 1) % grid.size());
                distance += (sx != x) || (sy != y);
                distance += abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y));
            }
        }
    }
    return distance;

}


int nMaxSwapDistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int sx = static_cast<int>((grid.at(x, y) - 1) / grid.size());
                int sy = static_cast<int>((grid.at(x, y) - 1) % grid.size());
                distance += abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y));
            }
        }
    }
    return distance;

}

int strange8DistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            int val = grid.at(x, y);
            if (val) {
                int sx = static_cast<int>((val - 1) / grid.size());
                int sy = static_cast<int>((val - 1) % grid.size());
                distance += 8 * (abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y)));
            }
        }
    }
    return distance;
}

int strange16DistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            int val = grid.at(x, y);
            if (val) {
                int sx = static_cast<int>((val - 1) / grid.size());
                int sy = static_cast<int>((val - 1) % grid.size());
                distance += 16 * (abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y)));
            }
        }
    }
    return distance;
}

int strange32DistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            int val = grid.at(x, y);
            if (val) {
                int sx = static_cast<int>((val - 1) / grid.size());
                int sy = static_cast<int>((val - 1) % grid.size());
                distance += 32 * (abs(sx - static_cast<int>(x)) + abs(sy - static_cast<int>(y)));
            }
        }
    }
    return distance;
}
