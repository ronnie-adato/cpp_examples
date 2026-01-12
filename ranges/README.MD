# Problem Description

A popular coding exercise involving half-open ranges is the **"Range Module"** problem, which
appears on LeetCode and other coding platforms. The problem involves designing a data structure to
add, remove, and query half-open intervals.

**Problem summary:**

> Design a data structure to track ranges of numbers. Implement the following methods:
>
> - `add_range(left, right)`: Adds the half-open interval [left, right) to the structure.
> - `remove_range(left, right)`: Removes the half-open interval [left, right) from the structure.
> - `query_range(left, right)`: Returns true if every number in the interval [left, right) is currently tracked.

**Reference:**

- [LeetCode 715. Range Module](https://leetcode.com/problems/range-module/)

```cpp
class Ranges {
public:
  void add_range(int left, int right);
  void remove_range(int left, int right);
  bool query_range(int left, int right);
};
```
