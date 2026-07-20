#pragma once

#include <gtest/gtest.h>
#include <memory>

class Solution;

template <typename T>
class CloneSolutionTypedTest : public ::testing::Test
{
   public:
    // Each typed test gets the concrete clone implementation under test.
    std::unique_ptr<Solution> solution = std::make_unique<T>();
};
