# Range Module (LeetCode 715, Hard)

LeetCode: <https://leetcode.com/problems/range-module/>

## Problem Description

Design a data structure that tracks half-open integer ranges of the form `[left, right)`.

It should support adding ranges, removing ranges, and querying whether every number in a requested
range is currently tracked.

## API

```cpp
class Ranges {
public:
  void add_range(int left, int right);
  void remove_range(int left, int right);
  bool query_range(int left, int right);
};
```
