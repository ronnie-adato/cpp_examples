#pragma once

#include "tree_node.hpp"

#include <unordered_map>
#include <vector>

class AllNodesDistanceK
{
   public:
    std::vector<int> distanceK(TreeNode* root, TreeNode* target, int k);

   private:
    void create_adj_list_(TreeNode* root, std::unordered_map<TreeNode*, std::vector<TreeNode*>>& adj_list);
};
