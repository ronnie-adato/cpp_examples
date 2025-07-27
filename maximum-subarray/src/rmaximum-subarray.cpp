
#include <ng-log/logging.h>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v)
{
    bool start = true;
    os << '[';
    for (const auto &n : v)
    {
        if (!start)
        {
            os << ", ";
        }
        else
        {
            start = false;
        }
        os << n;
    }
    os << ']';
    return os;
}

// int find_where_to_end(const std::vector<int> &nums)
// {
//     std::vector<int> sums(nums);
//     LOG(INFO) << "sums: " << sums;
//     int max_sum = sums.front();
//     int index = 0;
//     for (auto prev_it = sums.begin(), it = std::next(prev_it); it != sums.end(); prev_it = it, ++it)
//     {
//         *it += *prev_it;
//         if (max_sum < *it)
//         {
//             max_sum = *it;
//             index = std::distance(sums.begin(), it);
//         }
//     }
//     LOG(INFO) << "index: " << index << " max_sum: " << max_sum << " sums: " << sums;
//     return index;
// }

int maxSubArray(const std::vector<int> &nums)
{
    LOG(INFO) << "nums: " << nums;
    if (nums.empty())
    {
        LOG(INFO) << "Input is empty. Returning 0.";
        return 0;  // or throw an exception, depending on the desired behavior
    }

    // int left_index = find_where_to_end(nums);
    // int right_index = nums.size() - find_where_to_end(std::vector<int>(nums.rbegin(), nums.rend()));
    // int max_sum = std::accumulate(std::next(nums.begin(), left_index + 1), std::next(nums.begin(), right_index),
    //                               *std::next(nums.begin(), left_index));

    std::vector<int> sums(nums.crbegin(), nums.crend());

    int max_sum = sums.back();
    for (size_t i = sums.size() - 2; i != -1; --i)
    {
        sums[i] += sums[i + 1];
        if (max_sum < sums[i])
        {
            max_sum = sums[i];
        }
    }
    LOG(INFO) << "max_sum: " << max_sum << " sums: " << sums;

    while (sums.size() > 1)
    {
        int last = sums.back();
        sums.pop_back();
        for (auto it = sums.begin(); it != sums.end(); ++it)
        {
            *it -= last;
            if (max_sum < *it)
            {
                max_sum = *it;
            }
        }
        LOG(INFO) << "max_sum: " << max_sum << " sums: " << sums;
    }

    LOG(INFO) << "Returning max_sum: " << max_sum;
    return max_sum;
}
