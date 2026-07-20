#pragma once

#include <gtest/gtest.h>

#include <memory>

class Ranges;

template <typename T>
class RangesTypedTest : public ::testing::Test
{
   protected:
    // Store as the base type so tests cover the virtual interval API.
    std::unique_ptr<Ranges> rr = std::make_unique<T>();
};
