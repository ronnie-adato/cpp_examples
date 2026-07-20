#pragma once

#include <ostream>

struct Node
{
    int value;
    Node* next = nullptr;
    // Optional arbitrary pointer to another node in the same list.
    Node* afriend = nullptr;
};

auto operator<<(std::ostream& os, const Node& node) -> std::ostream&;
auto operator<<(std::ostream& os, const Node* node) -> std::ostream&;
