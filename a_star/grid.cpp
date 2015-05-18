#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>

#include <vector>
#include <queue>

#include "distance_estimators.h"
#include "grid.h"

using std::ostream;
using std::istream;
using std::vector;
using std::swap;

size_t Grid::size() const
{
    return grid_.size();
}

bool Grid::isValidPosition(int x, int y) const
{
    return 0 <= x && x < static_cast<int>(grid_.size()) && 
           0 <= y && y < static_cast<int>(grid_.size());
}

bool Grid::operator<(const Grid& rhs) const
{
    // essential, because otherwise doesn't differentiate objects with same distance
    // in set, map, etc.
    return grid_ < rhs.grid_; 
}

int& Grid::at(size_t i, size_t j)
{
    return grid_[i][j];
}

const int& Grid::at(size_t i, size_t j) const
{
    return grid_[i][j];
}

void Grid::findEmptyCell()
{
    for (size_t x = 0; x < grid_.size(); ++x) {
        for (size_t y = 0; y < grid_.size(); ++y) {
            if (at(x, y) == 0) {
                emptyCellX_ = x;
                emptyCellY_ = y;
                return;
            }
        }
    }
    assert(false && "Grid does not contain empty cell");
}

bool Grid::tryMove(int deltaX, int deltaY)
{
    int toX = emptyCellX_ + deltaX;
    int toY = emptyCellY_ + deltaY;

    // check if we can move 0-cell in this direction
    if (isValidPosition(toX, toY)) {
        // swap with toward cell
        swap(at(emptyCellX_, emptyCellY_),
             at(toX, toY)
        );

        // refresh 0-cell position
        emptyCellX_ = toX;
        emptyCellY_ = toY;
        return true;
    }
    return false;
}
