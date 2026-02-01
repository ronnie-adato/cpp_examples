#include <gtest/gtest.h>

#include "subarray_sum_k.hpp"

#include <cstddef>
#include <random>
#include <vector>

namespace
{

int subarraySumOracle(const std::vector<int>& nums, int k)
{
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

}  // namespace

TEST(SubarraySumKGenericTest, Empty)
{
    SubarraySumK solver;
    EXPECT_EQ(solver.subarraySum({}, 0), 0);
    EXPECT_EQ(solver.subarraySum({}, 5), 0);
}

TEST(SubarraySumKGenericTest, SingleElement)
{
    SubarraySumK solver;
    EXPECT_EQ(solver.subarraySum({5}, 5), 1);
    EXPECT_EQ(solver.subarraySum({5}, 0), 0);
    EXPECT_EQ(solver.subarraySum({-7}, -7), 1);
}

TEST(SubarraySumKGenericTest, LeetCodeExample)
{
    SubarraySumK solver;
    EXPECT_EQ(solver.subarraySum({1, 1, 1}, 2), 2);
}

TEST(SubarraySumKGenericTest, NonRotatedSimple)
{
    SubarraySumK solver;
    EXPECT_EQ(solver.subarraySum({1, 2, 3}, 3), 2);
}

TEST(SubarraySumKGenericTest, HandlesNegatives)
{
    SubarraySumK solver;
    EXPECT_EQ(solver.subarraySum({1, -1, 0}, 0), 3);
    EXPECT_EQ(solver.subarraySum({-1, -1, 1}, -1), 3);
}

TEST(SubarraySumKGenericTest, AllZeros)
{
    SubarraySumK solver;
    EXPECT_EQ(solver.subarraySum({0, 0, 0}, 0), 6);
    EXPECT_EQ(solver.subarraySum({0, 0, 0, 0}, 0), 10);
}

TEST(SubarraySumKGenericTest, RandomizedAgainstOracle)
{
    SubarraySumK solver;

    std::mt19937 rng(0xC0FFEE);
    std::uniform_int_distribution<int> nDist(0, 50);
    std::uniform_int_distribution<int> valDist(-5, 5);
    std::uniform_int_distribution<int> kDist(-10, 10);

    for (int iter = 0; iter < 500; ++iter)
    {
        const int n = nDist(rng);
        std::vector<int> nums;
        nums.reserve(static_cast<size_t>(n));
        for (int i = 0; i < n; ++i)
        {
            nums.push_back(valDist(rng));
        }

        const int k = kDist(rng);
        EXPECT_EQ(solver.subarraySum(nums, k), subarraySumOracle(nums, k))
            << "iter=" << iter << " n=" << n << " k=" << k;
    }
}
