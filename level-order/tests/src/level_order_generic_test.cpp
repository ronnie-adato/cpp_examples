#include <gtest/gtest.h>

#include "tree_node.hpp"

TEST(LevelOrderTraversal, Placeholder)
{
    TreeNode root;
    EXPECT_EQ(root.val, 0);
    EXPECT_EQ(root.left, nullptr);
    EXPECT_EQ(root.right, nullptr);
    SUCCEED();
}
