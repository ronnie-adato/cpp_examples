#pragma once

struct TreeNode;

// Returns the lowest tree node that has p and q in its subtree.
auto lowest_common_ancestor(TreeNode* root, TreeNode* p, TreeNode* q) -> TreeNode*;
