# Binary Tree Level Order Traversal (LeetCode 102, Medium)

LeetCode: <https://leetcode.com/problems/binary-tree-level-order-traversal/>

## Problem Description

Given the `root` of a binary tree, return the level order traversal of its nodes' values.
Level order means visiting nodes from left to right, level by level.

## Examples

```text
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
```

```text
Input: root = [1]
Output: [[1]]
```

```text
Input: root = []
Output: []
```

## Build / Test (Bazel)

- Build: `bazel build //level-order/...`
- Test: `bazel test //level-order/tests:tests-level_order`
