#include <vector>

#include "distance_estimators.h"

using std::vector;

int defaultDistanceEstimator(const Grid& grid)
{
    return manhattanDistanceEstimator(grid);
}

int manhattanLOrCDistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int supposedX = (grid.at(x, y) - 1) / static_cast<int>(grid.size());
                int supposedY = (grid.at(x, y) - 1) % static_cast<int>(grid.size());
                distance += abs(supposedX - x) + abs(supposedY - y);
                distance += (supposedX != static_cast<int>(x) || supposedY != static_cast<int>(y));
            }
        }
    }
    return distance;
}

int manhattanLAndCDistanceEstimator(const Grid& grid)
{
    int distance = 0;
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            if (grid.at(x, y)) {
                int supposedX = (grid.at(x, y) - 1) / static_cast<int>(grid.size());
                int supposedY = (grid.at(x, y) - 1) % static_cast<int>(grid.size());
                distance += abs(supposedX - x) + abs(supposedY - y);
                distance += (supposedX != static_cast<int>(x) && supposedY != static_cast<int>(y));
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
                int supposedX = (grid.at(x, y) - 1) / static_cast<int>(grid.size());
                int supposedY = (grid.at(x, y) - 1) % static_cast<int>(grid.size());
                distance += abs(supposedX - x) + abs(supposedY - y);
            }
        }
    }
    return distance;
}

int dijkstraDistanceEstimator(const Grid& grid)
{
    return 0;
}

