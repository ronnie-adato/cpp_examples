#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

class WordBreak
{
    struct TreeNode
    {
        std::string word;
        std::vector<std::shared_ptr<TreeNode>> children;
    };

    bool wordBreak(TreeNode *node, const std::string &s, const std::set<std::string> &wordDict);

   public:
    bool wordBreak(const std::string &s, const std::vector<std::string> &wordDict);
};
