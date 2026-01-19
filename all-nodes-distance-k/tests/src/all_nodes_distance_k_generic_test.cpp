#include <gtest/gtest.h>

#include "all_nodes_distance_k.hpp"

#include <algorithm>
#include <memory>
#include <vector>

namespace
{

struct TreeBuilder
{
    std::vector<std::unique_ptr<TreeNode>> nodes;

    TreeNode* Make(int val)
    {
        nodes.push_back(std::make_unique<TreeNode>(val));
        return nodes.back().get();
    }
};

std::vector<int> Sorted(std::vector<int> values)
{
    std::sort(values.begin(), values.end());
    return values;
}

}  // namespace

TEST(AllNodesDistanceKGenericTest, ExampleFromPrompt)
{
    // Tree:
    //       3
    //     /   \
    //    5     1
    //   / \   / \
    //  6   2 0   8
    //     / \
    //    7   4
    TreeBuilder tb;
    TreeNode* n3 = tb.Make(3);
    TreeNode* n5 = tb.Make(5);
    TreeNode* n1 = tb.Make(1);
    TreeNode* n6 = tb.Make(6);
    TreeNode* n2 = tb.Make(2);
    TreeNode* n0 = tb.Make(0);
    TreeNode* n8 = tb.Make(8);
    TreeNode* n7 = tb.Make(7);
    TreeNode* n4 = tb.Make(4);

    n3->left = n5;
    n3->right = n1;
    n5->left = n6;
    n5->right = n2;
    n1->left = n0;
    n1->right = n8;
    n2->left = n7;
    n2->right = n4;

    AllNodesDistanceK solver;

    const std::vector<int> got = Sorted(solver.distanceK(n3, n5, 2));
    const std::vector<int> want = Sorted({7, 4, 1});
    EXPECT_EQ(got, want);
}

TEST(AllNodesDistanceKGenericTest, KZeroReturnsTarget)
{
    TreeBuilder tb;
    TreeNode* root = tb.Make(1);
    root->left = tb.Make(2);
    root->right = tb.Make(3);

    AllNodesDistanceK solver;
    EXPECT_EQ(solver.distanceK(root, root->right, 0), std::vector<int>({3}));
}

TEST(AllNodesDistanceKGenericTest, SingleNodeTree)
{
    TreeBuilder tb;
    TreeNode* root = tb.Make(42);

    AllNodesDistanceK solver;
    EXPECT_EQ(solver.distanceK(root, root, 0), std::vector<int>({42}));
    EXPECT_TRUE(solver.distanceK(root, root, 1).empty());
}

TEST(AllNodesDistanceKGenericTest, TargetNotInTree)
{
    TreeBuilder tb;
    TreeNode* root = tb.Make(1);
    root->left = tb.Make(2);
    root->right = tb.Make(3);

    TreeNode detached(999);

    AllNodesDistanceK solver;
    EXPECT_TRUE(solver.distanceK(root, &detached, 1).empty());
}

TEST(AllNodesDistanceKGenericTest, NullInputsReturnEmpty)
{
    AllNodesDistanceK solver;
    EXPECT_TRUE(solver.distanceK(nullptr, nullptr, 0).empty());

    TreeBuilder tb;
    TreeNode* root = tb.Make(1);
    EXPECT_TRUE(solver.distanceK(root, nullptr, 0).empty());
}
