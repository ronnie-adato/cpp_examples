#include "subarray_sum_k.hpp"

#include <ng-log/logging.h>
#include <unordered_map>

int SubarraySumK::subarraySum(const std::vector<int>& nums, int k)
{
    LOG(INFO) << "SubarraySumK::subarraySum called (prefix-sum)";
    std::unordered_map<long long, int> count;
    count[0] = 1;

    long long sum = 0;
    int ans = 0;
    for (int x : nums)
    {
        sum += x;
        ans += count[sum - k];
        ++count[sum];
    }
    return ans;
}
