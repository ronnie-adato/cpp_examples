# Daily Temperatures (LeetCode 739, Medium)

LeetCode: <https://leetcode.com/problems/daily-temperatures/>

## Problem Description

Given an array of daily temperatures, return an array where each position contains the number of
days to wait until a warmer temperature.

If there is no future day with a warmer temperature, the value for that position is `0`.

## Examples

```text
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
```

```text
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
```

```text
Input: temperatures = [30,60,90]
Output: [1,1,0]
```

**Topics**: Monotonic Stack

## Build / Test (Bazel)

- Build: `bazel build //daily-temperatures/...`
- Test: `bazel test //daily-temperatures/tests:tests-daily-temperatures`
