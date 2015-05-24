#include <iostream>
#include <cstdlib>
#include <cassert>

#include <set>
#include <vector>
#include <queue>

#include "grid.h"
#include "solver.h"

using std::vector;
using std::set;
using std::cin;
using std::cout;
using std::cerr;
using std::priority_queue;
using std::ostream;

Movement movements[] {
    {0, 1,  EMove::RIGHT},
    {1, 0,  EMove::DOWN},
    {0, -1, EMove::LEFT},
    {-1, 0, EMove::UP}
};

void Solver::debugState(const Grid& grid) {
    cerr << "Estimated: " << estimate(grid, supposedX_, supposedY_) << '\n';
    cerr << "From start: " << dist_[grid] << '\n';
    cerr << '\n';
}

vector<Movement> Solver::restorePath()
{
    // restore the path from end to start
    Grid v = canonical_;

    vector<Movement> path;
    while (dist_[v]) {
        path.push_back(lastMove_[v]);

        bool hasMoved = v.tryMove(-lastMove_[v].deltaX, -lastMove_[v].deltaY); // move back
        assert(hasMoved); // back-route should be valid
    }

    // then reverse path
    reverse(path.begin(), path.end());

    return path;
}

inline void Solver::relaxState(const Grid& grid, int newDist, Movement newMove, int newDepth)
{
    bool notVisited = !dist_.count(grid);
    bool betterDist = (newDist < dist_[grid]);
    if (notVisited || betterDist) {
        if (!notVisited) {
            // delete old data
            auto it = stQueue_.lower_bound({dist_[grid], estimate(grid, supposedX_, supposedY_), grid, -1});
            assert(it != stQueue_.end());
            stQueue_.erase(it);
        }

        lastMove_[grid] = newMove;
        dist_[grid] = newDist;

        // insert new data
        stQueue_.insert({dist_[grid], estimate(grid, supposedX_, supposedY_), grid, newDepth});
    }
}

inline void Solver::traverseNeighbours(OrderedState& v)
{
    Grid grid = v.grid;

    for (auto& movement : movements) {
        bool hasMoved = grid.tryMove(movement.deltaX, movement.deltaY);

        relaxState(grid, v.distFromStart + 1, movement, v.depth + 1);

        // move back
        if (hasMoved) {
            assert(
                grid.tryMove(-movement.deltaX, -movement.deltaY)
            );
        }
    }
}

void Solver::prepare(Grid endGrid)
{
    // clear containers
    dist_.clear();
    lastMove_.clear();
    stQueue_ = set<OrderedState>();

    // set new goal
    canonical_ = endGrid;

    // calc places of values in canonical
    supposedX_.assign(endGrid.size() * endGrid.size(), 0);
    supposedY_.assign(endGrid.size() * endGrid.size(), 0);
    for (size_t i = 0; i < endGrid.size(); ++i) {
        for (size_t j = 0; j < endGrid.size(); ++j) {
            supposedX_[endGrid.at(i, j)] = i;
            supposedY_[endGrid.at(i, j)] = j;
        }
    }
}

vector<Movement> Solver::solve(Grid startGrid, Grid endGrid, bool debug, int depthLimit)
{
    prepare(endGrid);

    // push start (direction doesn't matter)
    relaxState(startGrid, 0, movements[0], 0);

    int timer = 0;
    while (!stQueue_.empty()) {
        ++timer;
        OrderedState v = *stQueue_.begin();
        stQueue_.erase(stQueue_.begin());

        bool hasReachedDepthLimit = (v.depth >= depthLimit);
        bool hasReachedGoal = (estimate(v.grid, supposedX_, supposedY_) == 0);

        if (hasReachedGoal) {
            break;
        }
        if (hasReachedDepthLimit) {
            continue;
        }

        if (debug && !(timer & 4095)) {
            debugState(v.grid);
        }
        
        // relax neihbours
        traverseNeighbours(v);
    }

    return restorePath();
}

void Solver::setEstimator(DistanceEstimator estimate)
{
    this->estimate = estimate;
}

// NOTE: 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0
// and size of puzzle is hardcoded here
bool Solver::isSolvable(const Grid& grid)
{
    int inversions = 0;
    size_t size = grid.size() * grid.size();

    bool blankOnOddRowFromBottom;

    for (int linearPos1 = 0; linearPos1 < size; ++linearPos1) {
        int value1 = grid.at(linearPos1);

        if (value1 == 0) {
            int x1 = linearPos1 / static_cast<int>(grid.size());
            blankOnOddRowFromBottom = (x1 % 2 == 1);
        }

        for (int linearPos2 = linearPos1 + 1; linearPos2 < size; ++linearPos2) {
            int value2 = grid.at(linearPos2);
            if (value1 > 0 && value2 > 0) {
                inversions += static_cast<int>(value1 > value2);
            }
        }
    }

    bool inversionsEven = (inversions % 2 == 0);
    return (blankOnOddRowFromBottom == inversionsEven);
}

// This compares distances as
// distance from start + heuristic distance to end
bool operator<(const OrderedState& lhs, const OrderedState& rhs) {
    int heuristicDistanceLhs = lhs.distFromStart + lhs.distToEnd;
    int heuristicDistanceRhs = rhs.distFromStart + rhs.distToEnd;
    if (heuristicDistanceLhs != heuristicDistanceRhs) {
        return heuristicDistanceLhs < heuristicDistanceRhs;
    }
    return lhs.grid < rhs.grid;
}


ostream& operator<<(ostream& out, const vector<Movement>& path)
{
    for (auto& x : path) {
        if (x.direction == EMove::LEFT) {
            out << 'L';
        } else if (x.direction == EMove::RIGHT) {
            out << 'R';
        } else if (x.direction == EMove::UP) {
            out << 'U';
        } else if (x.direction == EMove::DOWN) {
            out << 'D';
        } else {
            assert(false && "Direction should be either LEFT, RIGHT, UP or DOWN");
        }
    }
    out << '\n';
    return out;
}

