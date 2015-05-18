#ifndef _GRID_H_
#define _GRID_H_

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>

#include <vector>
#include <queue>

class Grid
{
public:
    // compare by distance_ value
    bool operator<(const Grid& rhs) const;

    friend std::ostream& operator<<(std::ostream& out, const Grid& rhs)
    {
        out << "Grid print:\n";
        for (size_t x = 0; x < rhs.grid_.size(); ++x) {
            for (size_t y = 0; y < rhs.grid_.size(); ++y) {
                out << rhs.grid_[x][y] << " \n"[y + 1 == rhs.grid_.size()];
            }
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Grid& rhs)
    {
        rhs.grid_ = std::vector<std::vector<int>>(4, std::vector<int>(4, 0));
        for (size_t x = 0; x < 4; ++x) {
            for (size_t y = 0; y < 4; ++y) {
                in >> rhs.grid_[x][y];
            }
        }
        rhs.findEmptyCell();
        return in;
    }

    size_t size() const;

    int& at(size_t i, size_t j);
    const int& at(size_t i, size_t j) const;

    bool tryMove(int deltaX, int deltaY);

private:
    // internal representation of grid as 2D matrix
    std::vector<std::vector<int>> grid_;

    // position of 0-cell
    int emptyCellX_;
    int emptyCellY_;

    bool isValidPosition(int x, int y) const;
    void findEmptyCell();
};

bool isSolvable(const Grid& grid);

#endif
