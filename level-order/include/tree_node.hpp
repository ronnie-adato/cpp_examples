#pragma once

struct TreeNode
{
    int val;
    // Raw child pointers match the simple LeetCode-style tree representation.
    TreeNode* left;
    TreeNode* right;

    TreeNode();
    explicit TreeNode(int x);
    TreeNode(int x, TreeNode* left, TreeNode* right);
};
