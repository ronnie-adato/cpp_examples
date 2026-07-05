# Maximum Subarray (LeetCode 53, Medium)

LeetCode: <https://leetcode.com/problems/maximum-subarray/>

## Problem Description

Given an integer array `nums`, find the contiguous non-empty subarray with the largest sum and
return that sum.

## Examples

```text
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
```

```text
Input: nums = [1]
Output: 1
```

```text
Input: nums = [5,4,-1,7,8]
Output: 23
```

## API

```cpp
int maxSubArray(std::vector<int>& nums);
```

## Build / Test (Bazel)

- Build: `bazel build //maximum-subarray/...`
- Test: `bazel test //maximum-subarray/tests:tests-maximum-subarray`
