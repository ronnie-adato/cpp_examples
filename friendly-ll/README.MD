# Copy List with Random Pointer (LeetCode 138, Medium)

LeetCode: <https://leetcode.com/problems/copy-list-with-random-pointer/>

## Problem Description

Given a linked list where each node has a regular `next` pointer and an arbitrary extra pointer,
return a deep copy of the list.

The copied list must contain new nodes with the same values, and each copied arbitrary pointer must
point to the corresponding copied node rather than to a node in the original list.

## Examples

```text
Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
```

```text
Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
```

```text
Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
```

In this module, the arbitrary pointer is named `afriend`:

```c++

struct Node {
  int value;
  Node *next = nullptr;
  Node *afriend = nullptr;
};

```

`afriend` may point to any other node in the list or be null. Friendship does not have to be mutual.

## Build / Test (Bazel)

- Build: `bazel build //friendly-ll/...`
- Test: `bazel test //friendly-ll/tests:tests-friendly-ll`
