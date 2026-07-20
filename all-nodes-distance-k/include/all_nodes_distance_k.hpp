#pragma once

#include "tree_node.hpp"

#include <unordered_map>
#include <vector>

class AllNodesDistanceK
{
   public:
    // Returns the values of all tree nodes exactly k edges away from target.
    std::vector<int> distanceK(TreeNode* root, TreeNode* target, int k);

   private:
    // Builds an undirected adjacency list from the binary tree links.
    void create_adj_list_(TreeNode* root, std::unordered_map<TreeNode*, std::vector<TreeNode*>>& adj_list);
};
