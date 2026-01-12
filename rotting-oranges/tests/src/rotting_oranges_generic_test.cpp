#include "rotting_oranges_test_fixture.hpp"

#include "rotting_oranges.hpp"

#include <array>
#include <cstddef>
#include <vector>

namespace
{

int reference_rotting_oranges_minutes(std::vector<std::vector<int>> grid)
{
    if (grid.empty())
    {
        return 0;
    }
    const size_t rows = grid.size();
    const size_t cols = grid[0].size();
    for (size_t r = 1; r < rows; ++r)
    {
        if (grid[r].size() != cols)
        {
            return -1;
        }
    }

    int fresh = 0;
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            if (grid[r][c] == 1)
            {
                ++fresh;
            }
        }
    }
    if (fresh == 0)
    {
        return 0;
    }

    int minutes = 0;
    const std::array<std::pair<int, int>, 4> dirs = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
    while (fresh > 0)
    {
        std::vector<std::pair<size_t, size_t>> to_rot;
        to_rot.reserve(static_cast<size_t>(fresh));

        for (size_t r = 0; r < rows; ++r)
        {
            for (size_t c = 0; c < cols; ++c)
            {
                if (grid[r][c] != 2)
                {
                    continue;
                }
                for (const auto& [dr, dc] : dirs)
                {
                    const int nr = static_cast<int>(r) + dr;
                    const int nc = static_cast<int>(c) + dc;
                    if (nr < 0 || nc < 0 || nr >= static_cast<int>(rows) || nc >= static_cast<int>(cols))
                    {
                        continue;
                    }
                    if (grid[static_cast<size_t>(nr)][static_cast<size_t>(nc)] == 1)
                    {
                        to_rot.emplace_back(static_cast<size_t>(nr), static_cast<size_t>(nc));
                    }
                }
            }
        }

        if (to_rot.empty())
        {
            return -1;
        }

        for (const auto& [r, c] : to_rot)
        {
            if (grid[r][c] == 1)
            {
                grid[r][c] = 2;
                --fresh;
            }
        }

        ++minutes;
    }

    return minutes;
}

std::vector<std::vector<int>> decode_ternary_grid(size_t rows, size_t cols, size_t value)
{
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));
    for (size_t idx = 0; idx < rows * cols; ++idx)
    {
        const int cell = static_cast<int>(value % 3);
        value /= 3;
        grid[idx / cols][idx % cols] = cell;
    }
    return grid;
}

}  // namespace

TEST_F(RottingOrangesTestFixture, EdgeCases)
{
    EXPECT_EQ(rotting_oranges_minutes({}), 0);
    EXPECT_EQ(rotting_oranges_minutes({{}}), 0);
    EXPECT_EQ(rotting_oranges_minutes({{0, 0}, {0, 0}}), 0);
    EXPECT_EQ(rotting_oranges_minutes({{2}}), 0);
    EXPECT_EQ(rotting_oranges_minutes({{1}}), -1);
}

TEST_F(RottingOrangesTestFixture, Examples)
{
    EXPECT_EQ(rotting_oranges_minutes({{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}), 4);
    EXPECT_EQ(rotting_oranges_minutes({{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}), -1);
    EXPECT_EQ(rotting_oranges_minutes({{0, 2}}), 0);
}

TEST_F(RottingOrangesTestFixture, MultiSourceAndShapes)
{
    EXPECT_EQ(rotting_oranges_minutes({{2, 2}, {1, 1}}), 1);
    EXPECT_EQ(rotting_oranges_minutes({{2, 1, 1, 1, 1}}), 4);
    EXPECT_EQ(rotting_oranges_minutes({{2}, {1}, {1}, {1}}), 3);
}

TEST_F(RottingOrangesTestFixture, DoesNotMutateInput)
{
    const std::vector<std::vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    const auto original = grid;
    (void)rotting_oranges_minutes(grid);
    EXPECT_EQ(grid, original);
}

TEST_F(RottingOrangesTestFixture, Exhaustive_3x3_AgreesWithReference)
{
    constexpr size_t rows = 3;
    constexpr size_t cols = 3;
    constexpr size_t cells = rows * cols;

    size_t total = 1;
    for (size_t i = 0; i < cells; ++i)
    {
        total *= 3;
    }

    for (size_t v = 0; v < total; ++v)
    {
        const auto grid = decode_ternary_grid(rows, cols, v);
        const int expected = reference_rotting_oranges_minutes(grid);
        const int actual = rotting_oranges_minutes(grid);
        if (expected != actual)
        {
            SCOPED_TRACE("Mismatch on 3x3 grid state " + std::to_string(v));
            EXPECT_EQ(actual, expected);
            return;
        }
    }
}
