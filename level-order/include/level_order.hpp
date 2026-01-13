#pragma once

#include <vector>

struct TreeNode;

// Returns the level-order traversal of the binary tree.
auto level_order_traversal(TreeNode* root) -> std::vector<std::vector<int>>;
