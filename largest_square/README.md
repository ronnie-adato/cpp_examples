# Maximal Square (LeetCode 221, Medium)

LeetCode: <https://leetcode.com/problems/maximal-square/>

## Problem Description

Given a binary matrix, find the largest square containing only `1` values.

LeetCode asks for the area of that square. This module uses the same problem shape, but its API
returns the side length and treats any non-zero integer cell as `1`.

## Examples

```text
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
LeetCode Output: 4
Module Output: 2
```

```text
Input: matrix = [["0","1"],["1","0"]]
LeetCode Output: 1
Module Output: 1
```

```text
Input: matrix = [["0"]]
LeetCode Output: 0
Module Output: 0
```

## Illustration

```text
Input grid:              Largest all-1 square:

1 0 1 0 0                . . . . .
1 0 1 1 1                . . [1 1] .
1 1 1 1 1                . . [1 1] .
1 0 0 1 0                . . . . .

LeetCode returns area = 4; this module returns side length = 2.
```

## API

```cpp
unsigned largest_square(const std::vector<std::vector<int>>& matrix);
```

The input matrix is treated as binary (any non-zero value counts as `1`).

## Notes

- Returns `0` for an empty matrix or when no non-zero square exists.

## Build / Test (Bazel)

- Build: `bazel build //largest_square/...`
- Test: `bazel test //largest_square/tests:tests-largest_square`
