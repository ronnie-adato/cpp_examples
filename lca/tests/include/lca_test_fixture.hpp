#pragma once

#include <gtest/gtest.h>

#include <memory>
#include <unordered_map>
#include <vector>

struct TreeNode;

struct LeastCommonAncestorTestFixture : public ::testing::Test
{
   protected:
    struct OwnedTree
    {
        // Own each allocated node while still exposing raw pointers to the API
        // under test, which mirrors the LeetCode-style function signature.
        TreeNode* make(int value);
        TreeNode* get(int value) const;

        std::vector<std::unique_ptr<TreeNode>> nodes;
        std::unordered_map<int, TreeNode*> by_value;
    };

    // Builds the canonical LeetCode 236 sample tree used by multiple cases.
    OwnedTree build_leetcode_236_example(TreeNode*& root);
};
