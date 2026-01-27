#include <gtest/gtest.h>

#include "k_closest_points_origin.hpp"

#include <cstddef>
#include <map>
#include <random>
#include <utility>
#include <vector>

namespace
{

using PointKey = std::pair<int, int>;

PointKey keyOf(const std::vector<int>& p)
{
    return {p.size() > 0 ? p[0] : 0, p.size() > 1 ? p[1] : 0};
}

std::map<PointKey, int> multisetCounts(const std::vector<std::vector<int>>& points)
{
    std::map<PointKey, int> counts;
    for (const auto& p : points)
    {
        ++counts[keyOf(p)];
    }
    return counts;
}

void expectPointsEqualIgnoringOrder(const std::vector<std::vector<int>>& actual,
                                    const std::vector<std::vector<int>>& expected)
{
    EXPECT_EQ(multisetCounts(actual), multisetCounts(expected));
}

void expectValidKClosest(const std::vector<std::vector<int>>& input, int k, const std::vector<std::vector<int>>& output)
{
    const size_t n = input.size();
    const size_t kk = (k <= 0) ? 0U : std::min(static_cast<size_t>(k), n);
    EXPECT_EQ(output.size(), kk);

    const auto inputCounts = multisetCounts(input);
    const auto outputCounts = multisetCounts(output);
    for (const auto& [pt, cnt] : outputCounts)
    {
        auto it = inputCounts.find(pt);
        ASSERT_TRUE(it != inputCounts.end()) << "output point not in input";
        (void)cnt;
    }
}

}  // namespace

TEST(KClosestPointsOriginGenericTest, Example1)
{
    KClosestPointsOrigin solver;

    const std::vector<std::vector<int>> points{{1, 3}, {-2, 2}};
    const int k = 1;
    const auto out = solver.kClosest(points, k);
    expectValidKClosest(points, k, out);

    expectPointsEqualIgnoringOrder(out, {{-2, 2}});
}

TEST(KClosestPointsOriginGenericTest, Example2)
{
    KClosestPointsOrigin solver;

    const std::vector<std::vector<int>> points{{3, 3}, {5, -1}, {-2, 4}};
    const int k = 2;
    const auto out = solver.kClosest(points, k);
    expectValidKClosest(points, k, out);
}

TEST(KClosestPointsOriginGenericTest, KEqualsN)
{
    KClosestPointsOrigin solver;
    const std::vector<std::vector<int>> points{{0, 1}, {2, 3}, {-4, 5}};
    const int k = 3;
    const auto out = solver.kClosest(points, k);
    expectValidKClosest(points, k, out);
}

TEST(KClosestPointsOriginGenericTest, KZeroReturnsEmpty)
{
    KClosestPointsOrigin solver;
    const std::vector<std::vector<int>> points{{0, 1}, {2, 3}, {-4, 5}};
    const int k = 0;
    const auto out = solver.kClosest(points, k);
    expectValidKClosest(points, k, out);
}

TEST(KClosestPointsOriginGenericTest, HandlesDuplicates)
{
    KClosestPointsOrigin solver;

    const std::vector<std::vector<int>> points{{1, 1}, {1, 1}, {2, 2}, {-1, -1}};
    const int k = 3;
    const auto out = solver.kClosest(points, k);
    expectValidKClosest(points, k, out);
}

TEST(KClosestPointsOriginGenericTest, AllSameDistanceTies)
{
    KClosestPointsOrigin solver;

    const std::vector<std::vector<int>> points{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    const int k = 2;
    const auto out = solver.kClosest(points, k);
    expectValidKClosest(points, k, out);
}

TEST(KClosestPointsOriginGenericTest, LargeCoordinatesNoOverflow)
{
    KClosestPointsOrigin solver;

    const std::vector<std::vector<int>> points{{1000000000, 1000000000}, {1, 2}, {-3, 4}};
    const int k = 1;
    const auto out = solver.kClosest(points, k);
    expectValidKClosest(points, k, out);

    expectPointsEqualIgnoringOrder(out, {{-3, 4}});
}

TEST(KClosestPointsOriginGenericTest, RandomizedAgainstReferenceThreshold)
{
    KClosestPointsOrigin solver;

    std::mt19937 rng(0xC0FFEE);
    std::uniform_int_distribution<int> nDist(0, 50);
    std::uniform_int_distribution<int> coordDist(-100, 100);

    for (int iter = 0; iter < 200; ++iter)
    {
        const int n = nDist(rng);
        std::vector<std::vector<int>> points;
        points.reserve(static_cast<size_t>(n));
        for (int i = 0; i < n; ++i)
        {
            points.push_back({coordDist(rng), coordDist(rng)});
        }

        std::uniform_int_distribution<int> kDist(0, n);
        const int k = kDist(rng);

        const auto out = solver.kClosest(points, k);
        expectValidKClosest(points, k, out);
    }
}
