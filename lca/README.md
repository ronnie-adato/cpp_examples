# Lowest Common Ancestor of a Binary Tree (LeetCode 236, Medium)

LeetCode: <https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/>

## Problem Description

Given the root of a binary tree and two nodes `p` and `q` in that tree, return their lowest common
ancestor.

The lowest common ancestor is the lowest node in the tree that has both `p` and `q` as descendants,
where a node may be a descendant of itself.

## Examples

```text
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
```

```text
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: A node can be a descendant of itself.
```

```text
Input: root = [1,2], p = 1, q = 2
Output: 1
```

## Build / Test (Bazel)

- Build: `bazel build //lca/...`
- Test: `bazel test //lca/tests:tests-lca`
