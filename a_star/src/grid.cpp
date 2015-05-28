#include <cmath>
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

Grid::Grid()
{}

Grid::Grid(const vector<int>& grid)
    : grid_(grid)
{
    size_ = sqrt(grid.size());

    // how ugly is that
    assert(size_ * size_ == grid.size());

    findEmptyCell();
}

size_t Grid::size() const
{
    return size_;
}

bool Grid::isValidPosition(int x, int y) const
{
    return 0 <= x && x < static_cast<int>(size()) && 
           0 <= y && y < static_cast<int>(size());
}

bool Grid::operator<(const Grid& rhs) const
{
    // essential, because otherwise doesn't differentiate objects with same distance
    // in set, map, etc.
    return grid_ < rhs.grid_; 
}

int& Grid::at(size_t idx)
{
    assert(idx < grid_.size());
    return grid_[idx];
}

const int& Grid::at(size_t idx) const
{
    assert(idx < grid_.size());
    return grid_[idx];
}

int& Grid::at(size_t i, size_t j)
{
    assert(i * size() + j < grid_.size());
    return grid_[i * size() + j];
}

const int& Grid::at(size_t i, size_t j) const
{
    assert(i * size() + j < grid_.size());
    return grid_[i * size() + j];
}

void Grid::findEmptyCell()
{
    for (size_t x = 0; x < size(); ++x) {
        for (size_t y = 0; y < size(); ++y) {
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
