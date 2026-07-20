#pragma once
#include <vector>

struct Node;

// Builds a list and connects afriend pointers by index; negative indexes mean
// no friend pointer for that node.
auto CreateLinkedList(const std::vector<int>& values, const std::vector<int>& afriend_indices) -> Node*;

// Deletes the next-linked chain; afriend pointers are non-owning.
void DeleteLinkedList(Node* root);
