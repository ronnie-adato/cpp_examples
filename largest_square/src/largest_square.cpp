#include "largest_square.hpp"

#include <ng-log/logging.h>

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& matrix)
{
    os << "[\n";
    for (const auto& row : matrix)
    {
        os << "  [";
        for (size_t j = 0; j < row.size(); ++j)
        {
            os << row[j];
            if (j + 1 < row.size())
            {
                os << ", ";
            }
        }
        os << "]\n";
    }
    os << "]";
    return os;
}

void make_binary(std::vector<std::vector<int>>& matrix)
{
    for (auto& row : matrix)
    {
        for (auto& cell : row)
        {
            cell = (cell != 0) ? 1 : 0;
        }
    }
}

unsigned largest_square(const std::vector<std::vector<int>>& matrix)
{
    if (matrix.empty() || matrix[0].empty())
    {
        return 0;
    }

    const size_t rows = matrix.size();
    const size_t cols = matrix[0].size();

    LOG(INFO) << "Matrix size: " << rows << "x" << cols;
    // std::cout << "Input matrix:\n" << matrix << std::endl;

    std::vector<std::vector<int>> binary_matrix = matrix;
    make_binary(binary_matrix);
    std::cout << "Binary matrix:\n" << binary_matrix << std::endl;

    std::vector<std::vector<int>> dp_left = binary_matrix;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = cols - 1; j != -1; --j)
        {
            if (j + 1 < cols && dp_left[i][j] > 0)
            {
                dp_left[i][j] += dp_left[i][j + 1];
            }
        }
    }
    std::cout << "DP Left matrix:\n" << dp_left << std::endl;

    std::vector<std::vector<int>> dp_down = binary_matrix;
    for (size_t i = rows - 1; i != -1; --i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            if (i + 1 < rows && dp_down[i][j] > 0)
            {
                dp_down[i][j] += dp_down[i + 1][j];
            }
        }
    }
    std::cout << "DP Down matrix:\n" << dp_down << std::endl;

    std::vector<std::vector<int>> dp = binary_matrix;
    unsigned max_square_length = 0;
    for (size_t i = rows - 1; i != -1; --i)
    {
        for (size_t j = cols - 1; j != -1; --j)
        {
            if (i + 1 < rows && j + 1 < cols && dp[i][j] != 0)
            {
                dp[i][j] = std::min({dp_left[i][j], dp_down[i][j], 1 + dp[i + 1][j + 1]});
            }
            if (dp[i][j] > max_square_length)
            {
                max_square_length = dp[i][j];
            }
        }
    }
    std::cout << "DP matrix:\n" << dp << std::endl;
    std::cout << "Largest square length: " << max_square_length << std::endl;

    return max_square_length;
}