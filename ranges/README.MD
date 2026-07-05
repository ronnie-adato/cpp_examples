# Range Module (LeetCode 715, Hard)

LeetCode: <https://leetcode.com/problems/range-module/>

## Problem Description

Design a data structure that tracks half-open integer ranges of the form `[left, right)`.

It should support adding ranges, removing ranges, and querying whether every number in a requested
range is currently tracked.

## Examples

```text
Input:
["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange"]
[[],[10,20],[14,16],[10,14],[13,15],[16,17]]
Output:
[null,null,null,true,false,true]
```

## Illustration

```mermaid
flowchart LR
    Start["tracked: empty"]
    Add["addRange(10, 20)<br/>tracked: [10, 20)"]
    Remove["removeRange(14, 16)<br/>tracked: [10, 14), [16, 20)"]
    Q1["queryRange(10, 14)<br/>true"]
    Q2["queryRange(13, 15)<br/>false"]
    Q3["queryRange(16, 17)<br/>true"]

    Start --> Add --> Remove
    Remove --> Q1
    Remove --> Q2
    Remove --> Q3
```

## API

```cpp
class Ranges {
public:
  void add_range(int left, int right);
  void remove_range(int left, int right);
  bool query_range(int left, int right);
};
```

## Build / Test (Bazel)

- Build: `bazel build //ranges/...`
- Test: `bazel test //ranges/tests:tests-ranges`
