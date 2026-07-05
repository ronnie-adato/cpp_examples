# K Closest Points to Origin (LeetCode 973, Medium)

LeetCode: <https://leetcode.com/problems/k-closest-points-to-origin/>

## Problem Description

Given an array of points on the X-Y plane and an integer `k`, return the `k` points closest to the
origin `(0, 0)`.

Distance is measured by Euclidean distance. The result may be returned in any order.

## Examples

```text
Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
```

```text
Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
```

**Topics**: Heap, Quickselect

## Build / Test (Bazel)

- Build: `bazel build //k-closest-points-origin/...`
- Test: `bazel test //k-closest-points-origin/tests:tests-k-closest-points-origin`
