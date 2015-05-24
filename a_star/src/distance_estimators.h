#ifndef _DISTANCE_ESTIMATOR_
#define _DISTANCE_ESTIMATOR_

#include <cstdlib>
#include <cassert>
#include <functional>

#include <vector>
#include <string>

#include "grid.h"

// type of estimate() function
typedef std::function<int (const Grid&, const std::vector<int>&, const std::vector<int>&)> DistanceEstimator;

int manhattanLAndCDistanceEstimator(const Grid& grid,
                                    const std::vector<int>& supposedX,
                                    const std::vector<int>& supposedY
                                    );
int linearConflictDistanceEstimator(const Grid& grid,
                                   const std::vector<int>& supposedX,
                                   const std::vector<int>& supposedY
                                   );
int manhattanDistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               );
int misplacedTilesDistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               );
int nMaxSwapDistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               );
int strange8DistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               );
int strange16DistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               );

int strange32DistanceEstimator(const Grid& grid,
                               const std::vector<int>& supposedX,
                               const std::vector<int>& supposedY
                               );

struct DEFunctionHolder
{
    DistanceEstimator function;
    std::string name;
};

#endif
