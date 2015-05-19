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

    Grid();
    Grid(const std::vector<int>& grid);

    // compare by distance_ value
    bool operator<(const Grid& rhs) const;

    friend std::ostream& operator<<(std::ostream& out, const Grid& grid)
    {
        out << "Grid\n";
        for (size_t x = 0; x < grid.size(); ++x) {
            for (size_t y = 0; y < grid.size(); ++y) {
                out << grid.at(x, y) << " \n"[y + 1 == grid.size()];
            }
        }
        out << '\n';
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Grid& grid)
    {
        grid.size_ = 4;
        grid.grid_ = std::vector<int>(grid.size() * grid.size(), 0);
        for (size_t x = 0; x < grid.size(); ++x) {
            for (size_t y = 0; y < grid.size(); ++y) {
                in >> grid.at(x, y);
            }
        }
        grid.findEmptyCell();
        return in;
    }

    size_t size() const;

    int& at(size_t i, size_t j);
    const int& at(size_t i, size_t j) const;

    bool tryMove(int deltaX, int deltaY);

private:
    // internal representation of grid as 2D matrix
    std::vector<int> grid_;

    // position of 0-cell
    int emptyCellX_;
    int emptyCellY_;

    size_t size_;

    bool isValidPosition(int x, int y) const;
    void findEmptyCell();
};

bool isSolvable(const Grid& grid);

#endif
