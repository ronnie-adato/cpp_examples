#include "word_break.hpp"

#include <ng-log/logging.h>

bool WordBreak::wordBreak(const std::string& s, const std::set<std::string_view>& wordDict)
{
    LOG(INFO) << "wordBreak entry: s: [" << s << "] dict_size=" << wordDict.size();
    if (s.empty())
    {
        LOG(INFO) << "wordBreak early-return: empty string -> true";
        return true;
    }

    std::string word;
    while (word.size() < s.size())
    {
        LOG(INFO) << "extend prefix: current=\"" << word << "\" next_char=\"" << s[word.size()]
                  << "\" remaining_len=" << s.size() - word.size();
        word.push_back(s[word.size()]);
        auto it = wordDict.lower_bound(word);
        if (it == wordDict.end() || word != it->substr(0, word.size()))
        {
            LOG(INFO) << "prefix rejected: \"" << word << "\"";
            break;
        }
        if (word == *it)
        {
            LOG(INFO) << "word hit: \"" << word << "\"; recursing";
            if (wordBreak(s.substr(word.size()), wordDict))
            {
                LOG(INFO) << "word break success at prefix: \"" << word << "\"";
                return true;
            }
            LOG(INFO) << "backtrack from prefix: \"" << word << "\"";
        }
    }

    return false;
}


bool WordBreak::wordBreak(const std::string& s, const std::vector<std::string>& wordDict)
{
    std::set<std::string_view> dict(wordDict.cbegin(), wordDict.cend());
    return wordBreak(s, dict);
}
