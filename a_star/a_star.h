#ifndef _A_STAR_H_
#define _A_STAR_H_

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>

#include <vector>
#include <map>
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
	std::vector<EMove> solve(Grid startGrid, bool debug = false, int depthLimit = 60);
	void setEstimator(DistanceEstimator estimate);


private:
	void relaxState(const Grid& grid, int newDist, Movement newMove, int newDepth);
	void traverseNeighbours(OrderedState& v);
	std::vector<EMove> restorePath();

	void debugState(const Grid& grid);

	DistanceEstimator estimate;

	Grid canonical_;

	std::map<Grid, int> dist_;
	std::map<Grid, Movement> lastMove_;
	std::priority_queue<OrderedState> stQueue_;
};
#endif
