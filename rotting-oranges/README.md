# Rotting Oranges (LeetCode 994)

LeetCode: https://leetcode.com/problems/rotting-oranges/

## Task

You are given a grid where:

- `0` = empty cell
- `1` = fresh orange
- `2` = rotten orange

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes until no fresh orange remains. If it’s impossible, return `-1`.

## Approach (BFS)

Use **multi-source BFS**:

- Push all initially-rotten cells into a queue.
- BFS level-by-level (each level = 1 minute).
- Track how many fresh oranges remain; if any are left at the end, return `-1`.

## Build / Test (Bazel)

- Build: `bazel build //rotting-oranges/...`
- Run only this module’s tests: `bazel test //rotting-oranges/tests:tests-rotting_oranges`
