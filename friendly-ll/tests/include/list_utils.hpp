#pragma once
#include <vector>

struct Node;

auto CreateLinkedList(const std::vector<int> &values, const std::vector<int> &afriend_indices) -> Node *;

void DeleteLinkedList(Node *root);
