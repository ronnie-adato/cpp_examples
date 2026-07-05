# Search in Rotated Sorted Array (LeetCode 33, Medium)

LeetCode: <https://leetcode.com/problems/search-in-rotated-sorted-array/>

## Problem Description

Given a sorted array of distinct integers that may have been rotated at an unknown pivot, return the
index of `target` if it exists in the array, or `-1` otherwise.

The intended solution should run in `O(log n)` time.

## Examples

```text
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
```

```text
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

```text
Input: nums = [1], target = 0
Output: -1
```

**Topics**: Binary Search

## Build / Test (Bazel)

- Build: `bazel build //search-rotated-array/...`
- Test: `bazel test //search-rotated-array/tests:tests-search-rotated-array`
