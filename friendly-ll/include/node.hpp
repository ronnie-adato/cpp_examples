#pragma once

#include <ostream>

struct Node {
  int value;
  Node *next = nullptr;
  Node *afriend = nullptr;
};

auto operator<<(std::ostream &os, const Node &node) -> std::ostream &;
auto operator<<(std::ostream &os, const Node *node) -> std::ostream &;

// Node constructor
