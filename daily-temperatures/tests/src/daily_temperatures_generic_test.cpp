#include <gtest/gtest.h>

#include "daily_temperatures.hpp"

#include <random>
#include <vector>

namespace
{

std::vector<int> bruteForceExpected(const std::vector<int> &temperatures)
{
    std::vector<int> result(temperatures.size(), 0);
    for (size_t i = 0; i < temperatures.size(); ++i)
    {
        for (size_t j = i + 1; j < temperatures.size(); ++j)
        {
            if (temperatures[j] > temperatures[i])
            {
                result[i] = static_cast<int>(j - i);
                break;
            }
        }
    }
    return result;
}

void expectSolution(const std::vector<int> &temperatures, const std::vector<int> &expected)
{
    DailyTemperatures solver;
    EXPECT_EQ(solver.dailyTemperatures(temperatures), expected);
}

}  // namespace

TEST(DailyTemperaturesGenericTest, Empty)
{
    expectSolution({}, {});
}

TEST(DailyTemperaturesGenericTest, SingleElement)
{
    expectSolution({42}, {0});
}

TEST(DailyTemperaturesGenericTest, LeetCodeExample1)
{
    expectSolution({73, 74, 75, 71, 69, 72, 76, 73}, {1, 1, 4, 2, 1, 1, 0, 0});
}

TEST(DailyTemperaturesGenericTest, LeetCodeExample2)
{
    expectSolution({30, 40, 50, 60}, {1, 1, 1, 0});
}

TEST(DailyTemperaturesGenericTest, LeetCodeExample3)
{
    expectSolution({30, 60, 90}, {1, 1, 0});
}

TEST(DailyTemperaturesGenericTest, StrictlyDecreasing)
{
    expectSolution({60, 50, 40, 30}, {0, 0, 0, 0});
}

TEST(DailyTemperaturesGenericTest, AllEqual)
{
    expectSolution({70, 70, 70, 70}, {0, 0, 0, 0});
}

TEST(DailyTemperaturesGenericTest, PlateausAndPeaks)
{
    // Next warmer for the initial 70 is the 71 at index 3.
    expectSolution({70, 70, 69, 71, 71, 70, 72}, {3, 2, 1, 3, 2, 1, 0});
}

TEST(DailyTemperaturesGenericTest, BruteForceAgreementRandomized)
{
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> lenDist(0, 50);
    std::uniform_int_distribution<int> tempDist(-20, 120);

    DailyTemperatures solver;
    for (int caseIdx = 0; caseIdx < 200; ++caseIdx)
    {
        const int n = lenDist(rng);
        std::vector<int> temperatures;
        temperatures.reserve(static_cast<size_t>(n));
        for (int i = 0; i < n; ++i)
        {
            temperatures.push_back(tempDist(rng));
        }

        const auto expected = bruteForceExpected(temperatures);
        const auto actual = solver.dailyTemperatures(temperatures);
        EXPECT_EQ(actual, expected) << "caseIdx=" << caseIdx;
    }
}
