#include <gtest/gtest.h>

#include "remove_k_digits.hpp"

TEST(RemoveKDigitsGenericTest, Examples)
{
    RemoveKDigits solver;
    EXPECT_EQ(solver.removeKdigits("1432219", 3), "1219");
    EXPECT_EQ(solver.removeKdigits("10200", 1), "200");
    EXPECT_EQ(solver.removeKdigits("10", 2), "0");
}

TEST(RemoveKDigitsGenericTest, EdgeCases)
{
    RemoveKDigits solver;

    EXPECT_EQ(solver.removeKdigits("9", 1), "0");
    EXPECT_EQ(solver.removeKdigits("112", 1), "11");
    EXPECT_EQ(solver.removeKdigits("10001", 1), "1");
    EXPECT_EQ(solver.removeKdigits("0000", 0), "0");
    EXPECT_EQ(solver.removeKdigits("00123", 0), "123");
    EXPECT_EQ(solver.removeKdigits("00123", 2), "1");
}
