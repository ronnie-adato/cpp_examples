#include "rotting_oranges.hpp"

#include <ng-log/logging.h>
#include <sys/types.h>
#include <cstddef>
#include <ostream>
#include <queue>

struct Cell
{
    size_t i;
    size_t j;
};

std::ostream& operator<<(std::ostream& os, const Cell& cell)
{
    os << "(" << cell.i << ", " << cell.j << ")";
    return os;
}

void add_to_queue(std::vector<std::vector<int>>& grid, std::queue<Cell>& q, size_t& good_oranges, const Cell& cell)
{
    grid[cell.i][cell.j] = 2;
    q.push(cell);
    --good_oranges;
}

int rotting_oranges_minutes(const std::vector<std::vector<int>>& grid)
{
    std::queue<Cell> q;
    size_t good_oranges = 0;

    const size_t rows = grid.size();
    if (rows == 0)
    {
        return 0;
    }
    const size_t cols = grid[0].size();
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < grid[0].size(); ++j)
        {
            if (grid[i][j] == 2)
            {
                q.push({i, j});
            }
            else if (grid[i][j] == 1)
            {
                ++good_oranges;
            }
        }
    }

    LOG(INFO) << "Initial good oranges: " << good_oranges << std::endl;
    size_t total_seconds = 0;
    std::vector<std::vector<int>> mygrid = grid;
    while (!q.empty() && good_oranges > 0)
    {
        ++total_seconds;
        size_t qsize = q.size();
        for (size_t i = 0; i < qsize; ++i)
        {
            Cell cell = q.front();
            q.pop();
            // down
            if (cell.i + 1 < rows && mygrid[cell.i + 1][cell.j] == 1)
            {
                add_to_queue(mygrid, q, good_oranges, {cell.i + 1, cell.j});
            }
            // up
            if (cell.i > 0 && mygrid[cell.i - 1][cell.j] == 1)
            {
                add_to_queue(mygrid, q, good_oranges, {cell.i - 1, cell.j});
            }
            // right
            if (cell.j + 1 < cols && mygrid[cell.i][cell.j + 1] == 1)
            {
                add_to_queue(mygrid, q, good_oranges, {cell.i, cell.j + 1});
            }
            // left
            if (cell.j > 0 && mygrid[cell.i][cell.j - 1] == 1)
            {
                add_to_queue(mygrid, q, good_oranges, {cell.i, cell.j - 1});
            }
        }
        if (q.empty())
        {
            --total_seconds;
        }
    }

    LOG(INFO) << "Good oranges remaining: " << good_oranges << " total seconds: " << total_seconds << std::endl;
    if (good_oranges == 0)
    {
        return total_seconds;
    }

    return -1;
}
