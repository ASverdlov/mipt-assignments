#ifndef _DISTANCE_ESTIMATOR_
#define _DISTANCE_ESTIMATOR_

#include <cstdlib>
#include <cassert>
#include <functional>

#include <vector>
#include <string>

#include "grid.h"

// type of estimate() function
typedef std::function<int (const Grid&)> DistanceEstimator;

int defaultDistanceEstimator(const Grid& grid);
int manhattanLCDistanceEstimator(const Grid& grid);
int manhattanDistanceEstimator(const Grid& grid);
int dijkstraDistanceEstimator(const Grid& grid);

struct DEFunctionHolder
{
    DistanceEstimator function;
    std::string name;
};

#endif
