#include "largest_square_generic_test.hpp"

#include "largest_square.hpp"

#include <gtest/gtest.h>
#include <ng-log/logging.h>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <random>


IntMatrix make_matrix(std::initializer_list<std::initializer_list<int>> rows)
{
	IntMatrix matrix;
	matrix.reserve(rows.size());
	for (const auto& row : rows)
	{
		matrix.emplace_back(row.begin(), row.end());
	}
	return matrix;
}

static bool is_rectangular(const IntMatrix& matrix)
{
	if (matrix.empty())
	{
		return true;
	}
	const std::size_t cols = matrix.front().size();
	for (const auto& row : matrix)
	{
		if (row.size() != cols)
		{
			return false;
		}
	}
	return true;
}

unsigned brute_force_largest_square(const IntMatrix& matrix)
{
	if (!is_rectangular(matrix))
	{
		// The production API doesn't specify ragged input; treat as "no valid square".
		return 0;
	}

	const std::size_t rows = matrix.size();
	if (rows == 0)
	{
		return 0;
	}
	const std::size_t cols = matrix.front().size();
	if (cols == 0)
	{
		return 0;
	}

	const std::size_t max_side = std::min(rows, cols);
	unsigned best = 0;
	for (std::size_t top = 0; top < rows; ++top)
	{
		for (std::size_t left = 0; left < cols; ++left)
		{
			for (std::size_t side = 1; side <= max_side; ++side)
			{
				if (top + side > rows || left + side > cols)
				{
					break;
				}

				bool all_ones = true;
				for (std::size_t r = top; r < top + side && all_ones; ++r)
				{
					for (std::size_t c = left; c < left + side; ++c)
					{
						if (matrix[r][c] == 0)
						{
							all_ones = false;
							break;
						}
					}
				}

				if (all_ones)
				{
					best = std::max(best, static_cast<unsigned>(side));
				}
			}
		}
	}
	return best;
}

static IntMatrix random_binary_matrix(
	std::size_t rows,
	std::size_t cols,
	double one_probability,
	std::mt19937& rng)
{
	std::bernoulli_distribution dist(one_probability);
	IntMatrix matrix(rows, std::vector<int>(cols, 0));
	for (std::size_t r = 0; r < rows; ++r)
	{
		for (std::size_t c = 0; c < cols; ++c)
		{
			matrix[r][c] = dist(rng) ? 1 : 0;
		}
	}
	return matrix;
}

TEST(LargestSquare, EmptyMatrixReturnsZero)
{
	const IntMatrix matrix;
	EXPECT_EQ(largest_square(matrix), 0u);
}

TEST(LargestSquare, MatrixWithEmptyRowReturnsZero)
{
	const IntMatrix matrix = {{} };
	EXPECT_EQ(largest_square(matrix), 0u);
}

TEST(LargestSquare, SingleCellZero)
{
	const IntMatrix matrix = make_matrix({{0}});
	EXPECT_EQ(largest_square(matrix), 0u);
}

TEST(LargestSquare, SingleCellOne)
{
	const IntMatrix matrix = make_matrix({{1}});
	EXPECT_EQ(largest_square(matrix), 1u);
}

TEST(LargestSquare, AllZeros)
{
	const IntMatrix matrix = make_matrix({{0, 0, 0}, {0, 0, 0}});
	EXPECT_EQ(largest_square(matrix), 0u);
}

TEST(LargestSquare, AllOnesSquare)
{
	const IntMatrix matrix = make_matrix({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
	EXPECT_EQ(largest_square(matrix), 3u);
}

TEST(LargestSquare, AllOnesRectangular)
{
	const IntMatrix matrix = make_matrix({{1, 1, 1, 1}, {1, 1, 1, 1}});
    LOG(INFO) << "Testing AllOnesRectangular with matrix size: " << matrix.size() << "x" << (matrix.empty() ? 0 : matrix[0].size());
	EXPECT_EQ(largest_square(matrix), 2u);
}

TEST(LargestSquare, SingleRow)
{
	const IntMatrix matrix = make_matrix({{1, 1, 1, 1, 1}});
	EXPECT_EQ(largest_square(matrix), 1u);
}

TEST(LargestSquare, SingleColumn)
{
	const IntMatrix matrix = make_matrix({{1}, {1}, {1}, {1}});
	EXPECT_EQ(largest_square(matrix), 1u);
}

TEST(LargestSquare, DiagonalOnesOnly)
{
	const IntMatrix matrix = make_matrix({
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	});
	EXPECT_EQ(largest_square(matrix), 1u);
}

TEST(LargestSquare, HolePreventsLargerSquare)
{
	const IntMatrix matrix = make_matrix({
		{1, 1, 1},
		{1, 0, 1},
		{1, 1, 1},
	});
	EXPECT_EQ(largest_square(matrix), 1u);
}

TEST(LargestSquare, ClassicExample)
{
	// Standard "maximal square" example where the answer is 2.
	const IntMatrix matrix = make_matrix({
		{1, 0, 1, 0, 0},
		{1, 0, 1, 1, 1},
		{1, 1, 1, 1, 1},
		{1, 0, 0, 1, 0},
	});
	EXPECT_EQ(largest_square(matrix), 2u);
}

TEST(LargestSquare, LargestSquareNotAtOrigin)
{
	const IntMatrix matrix = make_matrix({
		{0, 0, 0, 0},
		{0, 1, 1, 1},
		{0, 1, 1, 1},
		{0, 1, 1, 1},
	});
	EXPECT_EQ(largest_square(matrix), 3u);
}

TEST(LargestSquare, ValuesOtherThanZeroCountAsOne)
{
	// The implementation treats non-zero as "1".
	const IntMatrix matrix = make_matrix({
		{2, -1, 3},
		{5, 4, 6},
	});
	EXPECT_EQ(largest_square(matrix), 2u);
}

TEST(LargestSquare, DoesNotMutateInput)
{
	IntMatrix matrix = make_matrix({
		{1, 1, 0},
		{1, 1, 1},
	});
	const IntMatrix original = matrix;
	(void)largest_square(matrix);
	EXPECT_EQ(matrix, original);
}

TEST(LargestSquare, MatchesBruteForceOnSmallFixedCases)
{
	const std::vector<IntMatrix> cases = {
		make_matrix({{}}),
		make_matrix({{0, 0}, {0, 0}}),
		make_matrix({{1, 1}, {1, 1}}),
		make_matrix({{1, 0}, {1, 1}}),
		make_matrix({{0, 1, 1}, {1, 1, 1}}),
		make_matrix({{1, 1, 1}, {1, 1, 0}, {1, 1, 1}}),
	};

	for (const auto& matrix : cases)
	{
		EXPECT_EQ(largest_square(matrix), brute_force_largest_square(matrix));
	}
}

TEST(LargestSquare, RandomizedMatchesBruteForce)
{
	std::mt19937 rng(0xC0FFEEu);

	// Keep sizes small to make brute force fast.
	for (int trial = 0; trial < 200; ++trial)
	{
		const std::size_t rows = static_cast<std::size_t>(1 + (trial % 8));
		const std::size_t cols = static_cast<std::size_t>(1 + ((trial * 3) % 8));

		const double p = (trial % 5) * 0.2; // 0.0, 0.2, 0.4, 0.6, 0.8
		const IntMatrix matrix = random_binary_matrix(rows, cols, p, rng);

		const unsigned expected = brute_force_largest_square(matrix);
		const unsigned actual = largest_square(matrix);
		ASSERT_EQ(actual, expected) << "trial " << trial;
	}
}

