# Copy List with Random Pointer (LeetCode 138, Medium)

LeetCode: <https://leetcode.com/problems/copy-list-with-random-pointer/>

## Problem Description

Given a linked list where each node has a regular `next` pointer and an arbitrary extra pointer,
return a deep copy of the list.

The copied list must contain new nodes with the same values, and each copied arbitrary pointer must
point to the corresponding copied node rather than to a node in the original list.

In this module, the arbitrary pointer is named `afriend`:

```c++

struct Node {
  int value;
  Node *next = nullptr;
  Node *afriend = nullptr;
};

```

`afriend` may point to any other node in the list or be null. Friendship does not have to be mutual.
