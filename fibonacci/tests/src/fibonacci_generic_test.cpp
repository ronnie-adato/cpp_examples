
#include <gtest/gtest.h>
#include "../include/fibonacci_test_fixture.hpp"
#include "fibonacci.hpp"

TEST_F(FibonacciTestFixture, NegativeInput)
{
    EXPECT_THROW(fib.compute(-1), std::invalid_argument);
}

TEST_F(FibonacciTestFixture, ZeroInput)
{
    EXPECT_EQ(fib.compute(0), 0);
}

TEST_F(FibonacciTestFixture, BasicValues)
{
    EXPECT_EQ(fib.compute(0), 0);
    EXPECT_EQ(fib.compute(1), 1);
    EXPECT_EQ(fib.compute(2), 1);
    EXPECT_EQ(fib.compute(3), 2);
    EXPECT_EQ(fib.compute(4), 3);
    EXPECT_EQ(fib.compute(5), 5);
    EXPECT_EQ(fib.compute(6), 8);
    EXPECT_EQ(fib.compute(10), 55);
}

TEST_F(FibonacciTestFixture, LargerValues)
{
    EXPECT_EQ(fib.compute(20), 6765);
    EXPECT_EQ(fib.compute(30), 832040);
}
