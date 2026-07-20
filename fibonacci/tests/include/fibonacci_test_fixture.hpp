#pragma once
#include <gtest/gtest.h>
#include "fibonacci.hpp"

class FibonacciTestFixture : public ::testing::Test
{
   protected:
    // Shared instance lets tests exercise memoization across calls.
    Fibonacci fib;
};
