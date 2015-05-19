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
        out << "Grid\n";
        for (size_t x = 0; x < rhs.size(); ++x) {
            for (size_t y = 0; y < rhs.size(); ++y) {
                out << rhs.at(x, y) << " \n"[y + 1 == rhs.size()];
            }
        }
        out << '\n';
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Grid& rhs)
    {
        rhs.size_ = 4;
        rhs.grid_ = std::vector<int>(rhs.size() * rhs.size(), 0);
        for (size_t x = 0; x < rhs.size(); ++x) {
            for (size_t y = 0; y < rhs.size(); ++y) {
                in >> rhs.at(x, y);
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
