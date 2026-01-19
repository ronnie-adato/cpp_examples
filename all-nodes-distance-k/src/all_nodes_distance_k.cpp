#include "all_nodes_distance_k.hpp"

#include <ng-log/logging.h>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<int> AllNodesDistanceK::distanceK(TreeNode* root, TreeNode* target, int k)
{
    std::unordered_map<TreeNode*, std::vector<TreeNode*>> adj_list;
    std::vector<int> result;

    if (root == nullptr || target == nullptr || k < 0)
    {
        return result;
    }

    create_adj_list_(root, adj_list);
    auto it = adj_list.find(target);
    if (it == adj_list.end())
    {
        return result;
    }

    std::queue<TreeNode*> q;
    std::unordered_set<TreeNode*> visited;

    q.push(target);
    visited.insert(target);

    int distance = 0;
    while (!q.empty() && distance < k)
    {
        const size_t level_size = q.size();
        for (size_t i = 0; i < level_size; ++i)
        {
            TreeNode* node = q.front();
            q.pop();

            for (TreeNode* neighbor : adj_list[node])
            {
                if (neighbor == nullptr)
                {
                    continue;
                }
                if (visited.insert(neighbor).second)
                {
                    q.push(neighbor);
                }
            }
        }
        ++distance;
    }

    if (distance == k)
    {
        while (!q.empty())
        {
            result.push_back(q.front()->val);
            q.pop();
        }
    }

    return result;
}

void AllNodesDistanceK::create_adj_list_(TreeNode* root,
                                         std::unordered_map<TreeNode*, std::vector<TreeNode*>>& adj_list)
{
    if (root == nullptr)
    {
        return;
    }

    (void)adj_list[root];

    if (root->left != nullptr)
    {
        adj_list[root].push_back(root->left);
        adj_list[root->left].push_back(root);
        create_adj_list_(root->left, adj_list);
    }

    if (root->right != nullptr)
    {
        adj_list[root].push_back(root->right);
        adj_list[root->right].push_back(root);
        create_adj_list_(root->right, adj_list);
    }
}