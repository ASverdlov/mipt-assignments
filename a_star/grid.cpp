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

bool isSolvable(const Grid& grid)
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
