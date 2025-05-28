#pragma once

#include <gtest/gtest.h>

#include <memory>

class Ranges;

template <typename T>
class RangesTypedTest : public ::testing::Test {
protected:
    std::unique_ptr<Ranges> rr = std::make_unique<T>();
};

// Add other implementations here if needed
class RRanges;
typedef ::testing::Types<RRanges> RangeImplementations;

TYPED_TEST_SUITE(RangesTypedTest, RangeImplementations);

