#pragma once

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode();
    explicit TreeNode(int x);
    TreeNode(int x, TreeNode* left, TreeNode* right);
};
