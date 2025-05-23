# Problem Description

A linked list with friends is defined by the following node structure:

```c++

struct Node {
  int value;
  Node *next = nullptr;
  Node *afriend = nullptr;
};

```

`afriend` may point to any other node in the list or be null. Friendship doesn’t have to be mutual (i.e. a node pointed to by a friend pointer of another node, doesn’t have to point back).
Implement a clone function for such a list.
