#include "lca_test_fixture.hpp"
#include "tree_node.hpp"

TreeNode* LeastCommonAncestorTestFixture::OwnedTree::make(int value)
{
    nodes.emplace_back(std::make_unique<TreeNode>(value));
    TreeNode* ptr = nodes.back().get();
    by_value[value] = ptr;
    return ptr;
}

TreeNode* LeastCommonAncestorTestFixture::OwnedTree::get(int value) const
{
    auto it = by_value.find(value);
    return it == by_value.end() ? nullptr : it->second;
}

LeastCommonAncestorTestFixture::OwnedTree LeastCommonAncestorTestFixture::build_leetcode_236_example(TreeNode*& root)
{
    // Tree: [3,5,1,6,2,0,8,null,null,7,4]
    OwnedTree t;
    root = t.make(3);
    root->left = t.make(5);
    root->right = t.make(1);

    root->left->left = t.make(6);
    root->left->right = t.make(2);
    root->right->left = t.make(0);
    root->right->right = t.make(8);

    root->left->right->left = t.make(7);
    root->left->right->right = t.make(4);

    return t;
}
