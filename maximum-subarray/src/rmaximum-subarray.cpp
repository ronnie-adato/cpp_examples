
#include <ng-log/logging.h>
#include <cstddef>
#include <ostream>
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

int maxSubArray(const std::vector<int> &nums)
{
    LOG(INFO) << "nums: " << nums;
    if (nums.empty())
    {
        LOG(INFO) << "Input is empty. Returning 0.";
        return 0;  // or throw an exception, depending on the desired behavior
    }

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
