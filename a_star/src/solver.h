#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>

#include <vector>
#include <map>
#include <set>
#include <queue>

#include "grid.h"
#include "distance_estimators.h"

enum class EMove {
    RIGHT, DOWN, LEFT, UP
};

// This array holds directions info
struct Movement
{
    int deltaX;
    int deltaY;
    EMove direction;
}; 

struct OrderedState
{
    int distFromStart;
    int distToEnd;
    Grid grid;
    int depth;
};

class Solver
{
public:
    std::vector<Movement> solve(Grid source, bool debug = false, int depthLimit = 60);

    void setEstimator(DistanceEstimator estimate);
    static bool isSolvable(const Grid& grid);

private:
    void prepare();

    void relaxState(const Grid& grid, int newDist, Movement newMove, int newDepth);
    void traverseNeighbours(OrderedState& v);
    std::vector<Movement> restorePath();

    void debugState(const Grid& grid);

    DistanceEstimator estimate;

    Grid target_;

    std::map<Grid, int> dist_;
    std::map<Grid, Movement> lastMove_;
    std::set<OrderedState> stQueue_;
};

std::ostream& operator<<(std::ostream& out, const std::vector<Movement>& path);

bool operator<(const OrderedState& lhs, const OrderedState& rhs);

#endif
