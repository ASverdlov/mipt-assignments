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

int manhattanLAndCDistanceEstimator(const Grid& grid);
int linearConflictDistanceEstimator(const Grid& grid);
int manhattanDistanceEstimator(const Grid& grid);
int misplacedTilesDistanceEstimator(const Grid& grid);
int nMaxSwapDistanceEstimator(const Grid& grid);
int strange8DistanceEstimator(const Grid& grid);
int strange16DistanceEstimator(const Grid& grid);
int strange32DistanceEstimator(const Grid& grid);

struct DEFunctionHolder
{
    DistanceEstimator function;
    std::string name;
};

#endif
