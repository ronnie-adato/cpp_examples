#include "lca_test_fixture.hpp"

#include "lca.hpp"
#include "tree_node.hpp"

TEST_F(LeastCommonAncestorTestFixture, AllNullInputs_ReturnsNullptr)
{
    EXPECT_EQ(lowest_common_ancestor(nullptr, nullptr, nullptr), nullptr);
}

TEST_F(LeastCommonAncestorTestFixture, LeetCodeExample_P5_Q1_LCAIs3)
{
    TreeNode* root = nullptr;
    OwnedTree t = build_leetcode_236_example(root);

    TreeNode* p = t.get(5);
    TreeNode* q = t.get(1);
    ASSERT_NE(p, nullptr);
    ASSERT_NE(q, nullptr);

    EXPECT_EQ(lowest_common_ancestor(root, p, q), root);
}

TEST_F(LeastCommonAncestorTestFixture, LeetCodeExample_P5_Q4_LCAIs5)
{
    TreeNode* root = nullptr;
    OwnedTree t = build_leetcode_236_example(root);

    TreeNode* p = t.get(5);
    TreeNode* q = t.get(4);
    ASSERT_NE(p, nullptr);
    ASSERT_NE(q, nullptr);

    EXPECT_EQ(lowest_common_ancestor(root, p, q), p);
}

TEST_F(LeastCommonAncestorTestFixture, SingleNode_PEqualsQEqualsRoot)
{
    OwnedTree t;
    TreeNode* root = t.make(42);
    EXPECT_EQ(lowest_common_ancestor(root, root, root), root);
}

TEST_F(LeastCommonAncestorTestFixture, AncestorCase_ReturnsAncestor)
{
    // 1
    // |
    // 2
    // |
    // 3
    OwnedTree t;
    TreeNode* root = t.make(1);
    root->left = t.make(2);
    root->left->left = t.make(3);

    TreeNode* p = t.get(2);
    TreeNode* q = t.get(3);
    ASSERT_NE(p, nullptr);
    ASSERT_NE(q, nullptr);

    EXPECT_EQ(lowest_common_ancestor(root, p, q), p);
    EXPECT_EQ(lowest_common_ancestor(root, q, p), p);
}

TEST_F(LeastCommonAncestorTestFixture, NullInputs_ReturnsNullptr)
{
    OwnedTree t;
    TreeNode* root = t.make(1);
    TreeNode* p = root;

    EXPECT_EQ(lowest_common_ancestor(nullptr, p, p), nullptr);
    EXPECT_EQ(lowest_common_ancestor(root, nullptr, p), nullptr);
    EXPECT_EQ(lowest_common_ancestor(root, p, nullptr), nullptr);
}

TEST_F(LeastCommonAncestorTestFixture, NodeNotInTree_ReturnsNullptr)
{
    OwnedTree t;
    TreeNode* root = t.make(1);
    root->left = t.make(2);

    TreeNode orphan(99);
    EXPECT_EQ(lowest_common_ancestor(root, root->left, &orphan), nullptr);
}
