#pragma once

#include <vector>

class SearchRotatedArray
{
   public:
    int search(const std::vector<int>& nums, int target);

   private:
    int search(const std::vector<int>& nums, int target, const std::vector<int>::const_iterator& left,
               const std::vector<int>::const_iterator& right);
};
