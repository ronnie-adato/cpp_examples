#include "search_rotated_array.hpp"

#include <ng-log/logging.h>
#include <algorithm>
#include <iterator>

int SearchRotatedArray::search(const std::vector<int>& nums, int target)
{
    LOG(INFO) << "SearchRotatedArray::search called; n=" << nums.size() << ", target=" << target;
    return search(nums, target, nums.cbegin(), nums.cend());
}

int SearchRotatedArray::search(const std::vector<int>& nums, int target, const std::vector<int>::const_iterator& left,
                               const std::vector<int>::const_iterator& right)
{
    auto distance = std::distance(left, right);
    if (distance == 0 || left == nums.cend())
    {
        return -1;
    }

    const auto li = std::distance(nums.cbegin(), left);
    const auto ri = std::distance(nums.cbegin(), right);
    LOG(INFO) << "search(range=[" << li << "," << ri << "), dist=" << distance << ")";

    if (distance == 1)
    {
        if (*left == target)
        {
            return std::distance(nums.cbegin(), left);
        }
        return -1;
    }

    auto middle = std::next(left, distance / 2);

    int search_left = -1;
    const bool take_left = (((*left <= *std::prev(middle)) && (*left <= target && target <= *std::prev(middle))) ||
                            *left > *std::prev(middle));
    if (take_left)
    {
        LOG(INFO) << " -> recursing left";
        search_left = search(nums, target, left, middle);
    }

    int search_right = -1;
    const bool take_right = (((*middle <= *std::prev(right)) && (*middle <= target && target <= *std::prev(right))) ||
                             (*middle > *std::prev(right)));
    if (take_right)
    {
        LOG(INFO) << " -> recursing right";
        search_right = search(nums, target, middle, right);
    }

    return std::max(search_left, search_right);
}