#pragma once

#include <string>
#include <vector>

class WordBreak
{
   public:
    // Returns true when s can be segmented entirely into dictionary words.
    bool wordBreak(const std::string& s, const std::vector<std::string>& wordDict);
};
