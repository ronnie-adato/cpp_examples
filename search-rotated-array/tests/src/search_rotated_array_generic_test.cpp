#include <gtest/gtest.h>

#include "search_rotated_array.hpp"

#include <cstddef>
#include <random>
#include <unordered_set>
#include <vector>

namespace {

std::vector<int> makeIncreasingUnique(int n, int start, int step)
{
    std::vector<int> v;
    v.reserve(static_cast<size_t>(n));
    int cur = start;
    for (int i = 0; i < n; ++i)
    {
        v.push_back(cur);
        cur += step;
    }
    return v;
}

std::vector<int> rotateLeft(const std::vector<int>& v, size_t pivot)
{
    if (v.empty())
    {
        return {};
    }
    pivot %= v.size();
    std::vector<int> out;
    out.reserve(v.size());
    out.insert(out.end(), v.begin() + static_cast<std::ptrdiff_t>(pivot), v.end());
    out.insert(out.end(), v.begin(), v.begin() + static_cast<std::ptrdiff_t>(pivot));
    return out;
}

int linearSearchIndex(const std::vector<int>& v, int target)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (v[i] == target)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void expectCorrectIndexOrMinusOne(const std::vector<int>& nums, int target, int got)
{
    if (got == -1)
    {
        EXPECT_EQ(linearSearchIndex(nums, target), -1);
        return;
    }

    ASSERT_GE(got, 0);
    ASSERT_LT(static_cast<size_t>(got), nums.size());
    EXPECT_EQ(nums[static_cast<size_t>(got)], target);
}

}  // namespace

TEST(SearchRotatedArrayGenericTest, EmptyReturnsMinusOne)
{
    SearchRotatedArray solver;

    const std::vector<int> nums{};
    EXPECT_EQ(solver.search(nums, 1), -1);
}

TEST(SearchRotatedArrayGenericTest, SingleElementFound)
{
    SearchRotatedArray solver;

    const std::vector<int> nums{7};
    EXPECT_EQ(solver.search(nums, 7), 0);
}

TEST(SearchRotatedArrayGenericTest, SingleElementMissing)
{
    SearchRotatedArray solver;

    const std::vector<int> nums{7};
    EXPECT_EQ(solver.search(nums, 6), -1);
}

TEST(SearchRotatedArrayGenericTest, NotRotatedTypical)
{
    SearchRotatedArray solver;

    const std::vector<int> nums{1, 3, 5, 7, 9, 11};
    EXPECT_EQ(solver.search(nums, 1), 0);
    EXPECT_EQ(solver.search(nums, 11), 5);
    EXPECT_EQ(solver.search(nums, 7), 3);
    EXPECT_EQ(solver.search(nums, 8), -1);
}

TEST(SearchRotatedArrayGenericTest, RotatedExampleFromLeetCode)
{
    SearchRotatedArray solver;

    // Classic example: nums = [4,5,6,7,0,1,2]
    const std::vector<int> nums{4, 5, 6, 7, 0, 1, 2};
    EXPECT_EQ(solver.search(nums, 0), 4);
    EXPECT_EQ(solver.search(nums, 3), -1);
    EXPECT_EQ(solver.search(nums, 7), 3);
}

TEST(SearchRotatedArrayGenericTest, RotatedByEveryPivotFindAllElements)
{
    SearchRotatedArray solver;

    const auto base = makeIncreasingUnique(/*n=*/10, /*start=*/-20, /*step=*/3);
    for (size_t pivot = 0; pivot < base.size(); ++pivot)
    {
        const auto nums = rotateLeft(base, pivot);
        for (size_t i = 0; i < base.size(); ++i)
        {
            const int target = base[i];
            const int got = solver.search(nums, target);
            expectCorrectIndexOrMinusOne(nums, target, got);
        }
        EXPECT_EQ(solver.search(nums, 123456), -1);
    }
}

TEST(SearchRotatedArrayGenericTest, SmallArraysAllRotations)
{
    SearchRotatedArray solver;

    for (int n = 2; n <= 6; ++n)
    {
        const auto base = makeIncreasingUnique(n, /*start=*/10, /*step=*/2);
        for (size_t pivot = 0; pivot < static_cast<size_t>(n); ++pivot)
        {
            const auto nums = rotateLeft(base, pivot);

            // Check all present targets.
            for (int i = 0; i < n; ++i)
            {
                const int target = base[static_cast<size_t>(i)];
                const int got = solver.search(nums, target);
                expectCorrectIndexOrMinusOne(nums, target, got);
            }

            // Check some missing targets.
            EXPECT_EQ(solver.search(nums, base.front() - 1), -1);
            EXPECT_EQ(solver.search(nums, base.back() + 1), -1);
        }
    }
}

TEST(SearchRotatedArrayGenericTest, RandomizedAgainstLinearSearch)
{
    SearchRotatedArray solver;

    std::mt19937 rng(0xBADC0DE);
    std::uniform_int_distribution<int> nDist(0, 60);
    std::uniform_int_distribution<int> startDist(-200, 200);
    std::uniform_int_distribution<int> stepDist(1, 10);
    std::uniform_int_distribution<int> extraDist(-250, 250);

    for (int iter = 0; iter < 500; ++iter)
    {
        const int n = nDist(rng);
        const int start = startDist(rng);
        const int step = stepDist(rng);

        const auto base = makeIncreasingUnique(n, start, step);
        const size_t pivot = base.empty() ? 0U : static_cast<size_t>(rng() % base.size());
        const auto nums = rotateLeft(base, pivot);

        std::unordered_set<int> present;
        present.reserve(nums.size() * 2U + 1U);
        for (int x : nums)
        {
            present.insert(x);
        }

        // Try both present targets and random (often missing) targets.
        for (int q = 0; q < 50; ++q)
        {
            int target;
            if (!nums.empty() && (rng() % 2U == 0U))
            {
                target = nums[static_cast<size_t>(rng() % nums.size())];
            }
            else
            {
                target = extraDist(rng);
            }

            const int expected = linearSearchIndex(nums, target);
            const int got = solver.search(nums, target);

            // If expected is -1, got must be -1. Otherwise got must be a valid index with nums[got] == target.
            if (expected == -1)
            {
                EXPECT_EQ(got, -1);
            }
            else
            {
                expectCorrectIndexOrMinusOne(nums, target, got);
            }
        }
    }
}
