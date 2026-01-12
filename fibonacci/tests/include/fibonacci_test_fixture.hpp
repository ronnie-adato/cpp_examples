#pragma once
#include <gtest/gtest.h>
#include "fibonacci.hpp"

class FibonacciTestFixture : public ::testing::Test
{
   protected:
    Fibonacci fib;
};
