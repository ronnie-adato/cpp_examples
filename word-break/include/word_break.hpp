#pragma once

#include <set>
#include <string>
#include <vector>

class WordBreak
{
    bool wordBreak(const std::string& s, const std::set<std::string_view>& wordDict);

   public:
    bool wordBreak(const std::string& s, const std::vector<std::string>& wordDict);
};
