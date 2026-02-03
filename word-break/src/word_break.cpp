#include "word_break.hpp"

#include <ng-log/logging.h>
#include <algorithm>
#include <string_view>
#include <unordered_set>
#include <vector>

bool WordBreak::wordBreak(const std::string& s, const std::vector<std::string>& wordDict)
{
    LOG(INFO) << "wordBreak: s=\"" << s << "\" len=" << s.size() << " dict_size=" << wordDict.size();
    if (s.empty())
    {
        LOG(INFO) << "wordBreak: empty string -> true";
        return true;
    }

    std::unordered_set<std::string_view> dict;
    dict.reserve(wordDict.size());
    std::unordered_set<size_t> lengths;
    lengths.reserve(wordDict.size());
    size_t maxLen = 0;
    for (const auto& word : wordDict)
    {
        dict.insert(word);
        lengths.insert(word.size());
        maxLen = std::max(maxLen, word.size());
    }
    LOG(INFO) << "wordBreak: unique_words=" << dict.size() << " unique_lengths=" << lengths.size()
              << " maxLen=" << maxLen;

    std::vector<bool> dp(s.size() + 1, false);
    dp[0] = true;

    for (size_t i = 1; i <= s.size(); ++i)
    {
        const size_t upperLen = std::min(i, maxLen);
        for (const size_t len : lengths)
        {
            if (len == 0 || len > upperLen)
            {
                continue;
            }
            const size_t j = i - len;
            if (!dp[j])
            {
                continue;
            }
            const std::string_view slice(s.data() + j, len);
            if (dict.find(slice) != dict.end())
            {
                LOG(INFO) << "dp[" << i << "]=true via dp[" << j << "] and word=\"" << slice << "\"";
                dp[i] = true;
                break;
            }
        }
    }

    LOG(INFO) << "wordBreak: result=" << (dp[s.size()] ? "true" : "false");
    return dp[s.size()];
}
