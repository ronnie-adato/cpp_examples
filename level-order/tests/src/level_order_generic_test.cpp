#include <gtest/gtest.h>

#include "level_order.hpp"
#include "tree_node.hpp"

#include <cstddef>
#include <memory>
#include <random>
#include <utility>
#include <vector>

namespace
{

struct TreeArena
{
    std::vector<std::unique_ptr<TreeNode>> nodes;

    auto make(int value, TreeNode* left = nullptr, TreeNode* right = nullptr) -> TreeNode*
    {
        nodes.push_back(std::make_unique<TreeNode>(value, left, right));
        return nodes.back().get();
    }
};

auto level_order_reference_dfs(TreeNode* root) -> std::vector<std::vector<int>>
{
    std::vector<std::vector<int>> levels;

    const auto dfs = [&](auto&& self, TreeNode* node, std::size_t depth) -> void {
        if (node == nullptr) {
            return;
        }
        if (levels.size() == depth) {
            levels.push_back({});
        }
        levels[depth].push_back(node->val);
        self(self, node->left, depth + 1);
        self(self, node->right, depth + 1);
    };

    dfs(dfs, root, 0);
    return levels;
}

auto make_left_chain(TreeArena& arena, const std::vector<int>& values) -> TreeNode*
{
    TreeNode* root = nullptr;
    TreeNode* current = nullptr;
    for (int value : values) {
        TreeNode* node = arena.make(value);
        if (root == nullptr) {
            root = node;
            current = node;
            continue;
        }
        current->left = node;
        current = node;
    }
    return root;
}

auto make_right_chain(TreeArena& arena, const std::vector<int>& values) -> TreeNode*
{
    TreeNode* root = nullptr;
    TreeNode* current = nullptr;
    for (int value : values) {
        TreeNode* node = arena.make(value);
        if (root == nullptr) {
            root = node;
            current = node;
            continue;
        }
        current->right = node;
        current = node;
    }
    return root;
}

auto make_random_tree(TreeArena& arena, std::size_t node_count, std::mt19937& rng) -> TreeNode*
{
    if (node_count == 0) {
        return nullptr;
    }

    std::uniform_int_distribution<int> value_dist(-20, 20);
    std::uniform_int_distribution<int> side_dist(0, 1);

    TreeNode* root = arena.make(value_dist(rng));
    std::vector<TreeNode*> created;
    created.push_back(root);

    for (std::size_t i = 1; i < node_count; ++i) {
        TreeNode* new_node = arena.make(value_dist(rng));

        std::uniform_int_distribution<std::size_t> parent_dist(0, created.size() - 1);
        while (true) {
            TreeNode* parent = created[parent_dist(rng)];
            const bool attach_left = (side_dist(rng) == 0);
            if (attach_left) {
                if (parent->left == nullptr) {
                    parent->left = new_node;
                    break;
                }
            } else {
                if (parent->right == nullptr) {
                    parent->right = new_node;
                    break;
                }
            }
        }

        created.push_back(new_node);
    }

    return root;
}

} // namespace

TEST(LevelOrderTraversal, NullRoot)
{
    EXPECT_TRUE(level_order_traversal(nullptr).empty());
}

TEST(LevelOrderTraversal, SingleNode)
{
    TreeArena arena;
    TreeNode* root = arena.make(42);
    EXPECT_EQ(level_order_traversal(root), (std::vector<std::vector<int>>{{42}}));
}

TEST(LevelOrderTraversal, LeetCodeExample)
{
    // [3,9,20,null,null,15,7]
    TreeArena arena;
    TreeNode* n15 = arena.make(15);
    TreeNode* n7 = arena.make(7);
    TreeNode* n20 = arena.make(20, n15, n7);
    TreeNode* n9 = arena.make(9);
    TreeNode* root = arena.make(3, n9, n20);

    EXPECT_EQ(level_order_traversal(root), (std::vector<std::vector<int>>{{3}, {9, 20}, {15, 7}}));
}

TEST(LevelOrderTraversal, MissingChildren)
{
    //      1
    //     / \\.
    //    2   3
    //     \\.
    //      4
    TreeArena arena;
    TreeNode* n4 = arena.make(4);
    TreeNode* n2 = arena.make(2, nullptr, n4);
    TreeNode* n3 = arena.make(3);
    TreeNode* root = arena.make(1, n2, n3);

    EXPECT_EQ(level_order_traversal(root), (std::vector<std::vector<int>>{{1}, {2, 3}, {4}}));
}

TEST(LevelOrderTraversal, DuplicateValues)
{
    TreeArena arena;
    TreeNode* left = arena.make(1);
    TreeNode* right = arena.make(1);
    TreeNode* root = arena.make(1, left, right);
    EXPECT_EQ(level_order_traversal(root), (std::vector<std::vector<int>>{{1}, {1, 1}}));
}

TEST(LevelOrderTraversal, LeftSkewed)
{
    TreeArena arena;
    TreeNode* root = make_left_chain(arena, {1, 2, 3, 4, 5});
    EXPECT_EQ(level_order_traversal(root), (std::vector<std::vector<int>>{{1}, {2}, {3}, {4}, {5}}));
}

TEST(LevelOrderTraversal, RightSkewed)
{
    TreeArena arena;
    TreeNode* root = make_right_chain(arena, {1, 2, 3, 4, 5});
    EXPECT_EQ(level_order_traversal(root), (std::vector<std::vector<int>>{{1}, {2}, {3}, {4}, {5}}));
}

TEST(LevelOrderTraversal, RandomizedMatchesReference)
{
    std::mt19937 rng(1234567);
    std::uniform_int_distribution<std::size_t> size_dist(0, 50);

    for (int iter = 0; iter < 200; ++iter) {
        TreeArena arena;
        TreeNode* root = make_random_tree(arena, size_dist(rng), rng);

        const auto expected = level_order_reference_dfs(root);
        const auto actual = level_order_traversal(root);
        EXPECT_EQ(actual, expected) << "iter=" << iter;
    }
}
