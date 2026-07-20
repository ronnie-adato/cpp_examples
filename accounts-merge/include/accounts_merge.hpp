#pragma once

#include <string>
#include <vector>

class AccountsMerge
{
   public:
    // Merges accounts that share at least one email address.
    std::vector<std::vector<std::string>> accountsMerge(const std::vector<std::vector<std::string>>& accounts);
};
