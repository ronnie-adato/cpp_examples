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
		TreeNode* make(int value);
		TreeNode* get(int value) const;

		std::vector<std::unique_ptr<TreeNode>> nodes;
		std::unordered_map<int, TreeNode*> by_value;
	};

	OwnedTree build_leetcode_236_example(TreeNode*& root);
};
