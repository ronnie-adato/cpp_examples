#pragma once

#include <initializer_list>
#include <vector>

// Shared utilities for LargestSquare tests.

using IntMatrix = std::vector<std::vector<int>>;

IntMatrix make_matrix(std::initializer_list<std::initializer_list<int>> rows);

// Brute-force oracle for validating expected results on small inputs.
unsigned brute_force_largest_square(const IntMatrix& matrix);