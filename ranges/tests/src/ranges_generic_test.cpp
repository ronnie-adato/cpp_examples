#include "ranges_generic_test.hpp"
#include "rranges.hpp"

#include <ng-log/logging.h>

// Add other implementations here if needed
typedef ::testing::Types<RRanges> RangeImplementations;

TYPED_TEST_SUITE(RangesTypedTest, RangeImplementations);


TYPED_TEST(RangesTypedTest, AddAndQuerySimpleRange) {
    this->rr->add_range(1, 5);
    // LOG(INFO) << *this->rr;
    EXPECT_TRUE(this->rr->query_range(1, 5));
    EXPECT_FALSE(this->rr->query_range(0, 1));
    EXPECT_FALSE(this->rr->query_range(5, 6));
}

TYPED_TEST(RangesTypedTest, AddOverlappingRanges) {
    this->rr->add_range(1, 5);
    this->rr->add_range(3, 7);
    EXPECT_TRUE(this->rr->query_range(1, 7));
    EXPECT_FALSE(this->rr->query_range(0, 1));
    EXPECT_FALSE(this->rr->query_range(7, 8));
}

TYPED_TEST(RangesTypedTest, RemoveRange) {
    this->rr->add_range(1, 10);
    this->rr->remove_range(3, 7);
    EXPECT_TRUE(this->rr->query_range(1, 3));
    EXPECT_TRUE(this->rr->query_range(7, 10));
    EXPECT_FALSE(this->rr->query_range(3, 7));
    EXPECT_FALSE(this->rr->query_range(2, 8));
}

TYPED_TEST(RangesTypedTest, RemoveNonOverlappingRange) {
    this->rr->add_range(1, 5);
    this->rr->remove_range(6, 8);
    EXPECT_TRUE(this->rr->query_range(1, 5));
}

TYPED_TEST(RangesTypedTest, AddRemoveAndQueryEdgeCases) {
    this->rr->add_range(1, 5);
    this->rr->add_range(10, 15);
    this->rr->remove_range(3, 12);
    EXPECT_TRUE(this->rr->query_range(1, 3));
    EXPECT_TRUE(this->rr->query_range(12, 15));
    EXPECT_FALSE(this->rr->query_range(3, 12));
}

TYPED_TEST(RangesTypedTest, InvalidRanges) {
    this->rr->add_range(5, 5);
    this->rr->remove_range(7, 7);
    EXPECT_FALSE(this->rr->query_range(10, 9));
    EXPECT_FALSE(this->rr->query_range(5, 5));
}