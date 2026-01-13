#include "level_order.hpp"
#include "tree_node.hpp"

#include <cstddef>
#include <queue>

auto level_order_traversal(TreeNode* root) -> std::vector<std::vector<int>>
{
    std::vector<std::vector<int>> traversed_tree;
    if (root == nullptr)
    {
        return traversed_tree;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty())
    {
        const std::size_t level_size = q.size();
        traversed_tree.push_back({});
        traversed_tree.back().reserve(level_size);

        for (std::size_t i = 0; i < level_size; ++i)
        {
            TreeNode* node = q.front();
            q.pop();

            traversed_tree.back().push_back(node->val);
            if (node->left != nullptr)
            {
                q.push(node->left);
            }
            if (node->right != nullptr)
            {
                q.push(node->right);
            }
        }
    }

    return traversed_tree;
}
