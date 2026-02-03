#include "word_break.hpp"

#include <ng-log/logging.h>
#include <cstddef>
#include <memory>

bool WordBreak::wordBreak(const std::string& s, const std::vector<std::string>& wordDict)
{
    LOG(INFO) << "wordBreak entry: s: [" << s << "] dict_size=" << wordDict.size();
    std::set<std::string> dict(wordDict.cbegin(), wordDict.cend());
    if (s.empty())
    {
        LOG(INFO) << "wordBreak early-return: empty string -> true";
        return true;
    }

    TreeNode node;
    const bool result = wordBreak(&node, s, dict);
    LOG(INFO) << "wordBreak exit: result=" << (result ? "true" : "false") << " s_len=" << s.size();
    return result;
}

bool WordBreak::wordBreak(TreeNode* node, const std::string& s, const std::set<std::string>& wordDict)
{
    LOG(INFO) << "wordBreak entry: s: [" << s << "], node->word: [" << node->word << "]";
    while (node->word.size() < s.size())
    {
        LOG(INFO) << "extend prefix: current=\"" << node->word << "\" next_char=\"" << s[node->word.size()]
                  << "\" remaining_len=" << s.size() - node->word.size();
        node->word.push_back(s[node->word.size()]);
        auto it = wordDict.lower_bound(node->word);
        if (it == wordDict.end() || node->word != it->substr(0, node->word.size()))
        {
            LOG(INFO) << "prefix rejected: \"" << node->word << "\"";
            node->word.pop_back();
            return false;
        }
        if (node->word == *it)
        {
            LOG(INFO) << "word hit: \"" << node->word << "\"; recursing";
            node->children.emplace_back(std::make_shared<TreeNode>());
            if (wordBreak(node->children.back().get(), s.substr(node->word.size()), wordDict))
            {
                LOG(INFO) << "word break success at prefix: \"" << node->word << "\"";
                return true;
            }
            LOG(INFO) << "backtrack from prefix: \"" << node->word << "\"";
        }
    }

    if (s.empty())
    {
        LOG(INFO) << "wordBreak early-return: empty string -> true";
        return true;
    }
    LOG(INFO) << "exhausted prefix: \"" << node->word << "\"";

    return wordDict.find(node->word) != wordDict.end();
}