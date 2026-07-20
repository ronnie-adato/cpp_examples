#include "subarray_sum_k.hpp"

#include <ng-log/logging.h>
#include <unordered_map>

int SubarraySumK::subarraySum(const std::vector<int>& nums, int k)
{
    LOG(INFO) << "SubarraySumK::subarraySum called (prefix-sum)";
    std::unordered_map<long long, int> count;
    // Empty prefix lets subarrays starting at index 0 be counted naturally.
    count[0] = 1;

    long long sum = 0;
    int ans = 0;
    for (int x : nums)
    {
        sum += x;
        // Any previous prefix of sum-k forms a subarray ending here with sum k.
        ans += count[sum - k];
        ++count[sum];
    }
    return ans;
}
