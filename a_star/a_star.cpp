#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>

#include <vector>
#include <map>
#include <queue>

#include "grid.h"
#include "a_star.h"

using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::map;
using std::priority_queue;
using std::ostream;

Movement movements[] {
	{0, 1,  EMove::RIGHT},
	{1, 0,  EMove::DOWN},
	{0, -1, EMove::LEFT},
	{-1, 0, EMove::UP}
};

// compare by "bigger", because priority_queue sorts by "bigger"
// and we want to sort by "less"
bool operator<(const OrderedState& lhs, const OrderedState& rhs) {
	// this compares distances as
	// distance from start + heuristic distance to end
	int heuristicDistanceLhs = lhs.distFromStart + lhs.distToEnd;
	int heuristicDistanceRhs = rhs.distFromStart + rhs.distToEnd;
	if (heuristicDistanceLhs != heuristicDistanceRhs) {
		return heuristicDistanceLhs > heuristicDistanceRhs;
	}
	return lhs.grid < rhs.grid;
}

void Solver::debugState(const Grid& grid) {
	cerr << "Estimated: " << estimate(grid) << '\n';
	cerr << "From start: " << dist_[grid] << '\n';
	cerr << '\n';
}

vector<EMove> Solver::restorePath()
{
	// restore the path from end to start
	Grid v = canonical_;

	vector<EMove> path;
	while (dist_[v]) {
		path.push_back(lastMove_[v].direction);

		bool hasMoved = v.tryMove(-lastMove_[v].deltaX, -lastMove_[v].deltaY); // move back
		assert(hasMoved); // back-route should be valid
	}

	// then reverse path
	reverse(path.begin(), path.end());

	return path;
}

void Solver::relaxState(const Grid& grid, int newDist, Movement newMove, int newDepth)
{
	bool notVisited = !dist_.count(grid);
	bool betterDist = (newDist < dist_[grid]);
	if (notVisited || betterDist) {
		lastMove_[grid] = newMove;
		dist_[grid] = newDist;

		// NOTE: we don't delete old state from heap
		stQueue_.push({dist_[grid], estimate(grid), grid, newDepth});
	}
}

void Solver::traverseNeighbours(OrderedState& v)
{
	// reuse existing state
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

vector<EMove> Solver::solve(Grid startGrid, bool debug, int depthLimit)
{
	dist_.clear();
	lastMove_.clear();
	stQueue_ = priority_queue<OrderedState>();

	// push start (direction doesn't matter)
	relaxState(startGrid, 0, movements[0], 0);

	int timer = 0;
	while (!stQueue_.empty()) {
		++timer;
		OrderedState v = stQueue_.top();
		stQueue_.pop();

		// priority_queue doesn't provide any delete function
		// so instead of deleting here we check if v contains shortest distance
		// gained so far

		bool isActualDistance = (dist_[v.grid] == v.distFromStart);
		bool hasReachedDepthLimit = (v.depth >= depthLimit);
		bool hasReachedGoal = (estimate(v.grid) == 0);

		if (!isActualDistance || hasReachedDepthLimit) {
			continue;
		}
		if (hasReachedGoal) {
			canonical_ = v.grid;
			break;
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

ostream& operator<<(ostream& out, const vector<EMove>& path)
{
	for (auto& x : path) {
		if (x == EMove::LEFT) {
			out << 'L';
		} else if (x == EMove::RIGHT) {
			out << 'R';
		} else if (x == EMove::UP) {
			out << 'U';
		} else {
			assert(x == EMove::DOWN);
			out << 'D';
		}
	}
	out << '\n';
	return out;
}

static bool isSolvable(const Grid& grid)
{
	int inversions = 0;
	size_t size = grid.size() * grid.size();

	bool blankOnOddRowFromBottom;

	for (int linearPos1 = 0; linearPos1 < size; ++linearPos1) {
		int x1 = linearPos1 / static_cast<int>(grid.size());
		int y1 = linearPos1 % static_cast<int>(grid.size());
		int value1 = grid.at(x1, y1);

		if (value1 == 0) {
			blankOnOddRowFromBottom = (x1 % 2 != 1);
		}

		for (int linearPos2 = linearPos1 + 1; linearPos2 < size; ++linearPos2) {
			int x2 = linearPos2 / static_cast<int>(grid.size());
			int y2 = linearPos2 / static_cast<int>(grid.size());
			int value2 = grid.at(x2, y2);

			bool isInversion = false;
			if (grid.at(x1, y1) > 0 && grid.at(x2, y2) > 0) {
				isInversion = (value1 > value2);
			} else {
				isInversion = (value1 == 0);
			}
			inversions += isInversion;
		}
	}

	bool inversionsEven = (inversions % 2 == 0);
	return (blankOnOddRowFromBottom == inversionsEven);
}

int main()
{
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	DEFunctionHolder distEstimators[1] = {
		{manhattanLCDistanceEstimator, "Manhattan + L or C"}
	};

	Solver solver;

	int T; cin >> T;
	for (int test = 1; test <= T; ++test) {
		Grid grid;
		cin >> grid;
		cout << grid;
		
		std::cout << "Test: " << test << ":\n";

		if (!isSolvable(grid)) {
			cout << "This puzzle is not solvable.\n";
			continue;
		}

		for (const auto& estimatorHolder : distEstimators) {
			clock_t startTime = clock();

			solver.setEstimator(estimatorHolder.function);

			vector<EMove> ans = solver.solve(grid, false);

			double elapsedTime = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;
			std::cout << "\tWith estimator: " << estimatorHolder.name << ", time: " << elapsedTime
					  << ", answer: " << ans << '\n';
		}
	}
	return 0;
}
