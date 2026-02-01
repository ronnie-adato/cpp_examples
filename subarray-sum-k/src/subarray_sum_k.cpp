#include "subarray_sum_k.hpp"

#include <ng-log/logging.h>

#include <cstddef>

int SubarraySumK::subarraySum(const std::vector<int>& nums, int k)
{
    LOG(INFO) << "SubarraySumK::subarraySum called (naive)";

    long long count = 0;
    for (size_t i = 0; i < nums.size(); ++i)
    {
        long long sum = 0;
        for (size_t j = i; j < nums.size(); ++j)
        {
            sum += nums[j];
            if (sum == static_cast<long long>(k))
            {
                ++count;
            }
        }
    }
    return static_cast<int>(count);
}
