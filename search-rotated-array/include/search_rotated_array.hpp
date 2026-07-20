#pragma once

#include <vector>

class SearchRotatedArray
{
   public:
    // Returns the index of target in a rotated sorted array, or -1 if missing.
    int search(const std::vector<int>& nums, int target);

   private:
    // Searches the half-open range [left, right).
    int search(const std::vector<int>& nums, int target, const std::vector<int>::const_iterator& left,
               const std::vector<int>::const_iterator& right);
};
