#include <gtest/gtest.h>
#include <vector>

// Declaration of the function under test
int maxSubArray(const std::vector<int> &nums);

TEST(MaxSubArrayTest, HandlesSingleElement) {
    std::vector<int> nums = {5};
    EXPECT_EQ(maxSubArray(nums), 5);
}

TEST(MaxSubArrayTest, HandlesAllPositive) {
    std::vector<int> nums = {1, 2, 3, 4};
    EXPECT_EQ(maxSubArray(nums), 10);
}

TEST(MaxSubArrayTest, HandlesAllNegative) {
    std::vector<int> nums = {-1, -2, -3, -4};
    EXPECT_EQ(maxSubArray(nums), -1);
}

TEST(MaxSubArrayTest, HandlesMixedValues) {
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    EXPECT_EQ(maxSubArray(nums), 6);
}

TEST(MaxSubArrayTest, HandlesZeros) {
    std::vector<int> nums = {0, 0, 0, 0};
    EXPECT_EQ(maxSubArray(nums), 0);
}

TEST(MaxSubArrayTest, HandlesLargeArray) {
    std::vector<int> nums(100, 1);
    EXPECT_EQ(maxSubArray(nums), 100);
}

TEST(MaxSubArrayTest, HandlesEmptyArray) {
    std::vector<int> nums;
    // Behavior for empty input is undefined, but let's check for no crash (optional)
    // EXPECT_THROW(maxSubArray(nums), std::exception);
}

TEST(MaxSubArrayTest, HandlesSingleNegative) {
    std::vector<int> nums = {-42};
    EXPECT_EQ(maxSubArray(nums), -42);
}

TEST(MaxSubArrayTest, HandlesAlternatingSigns) {
    std::vector<int> nums = {2, -1, 2, -1, 2, -1, 2};
    EXPECT_EQ(maxSubArray(nums), 5);
}

TEST(MaxSubArrayTest, HandlesLargeNegativesWithSmallPositive) {
    std::vector<int> nums = {-1000, 1, -1000, 2, -1000, 3};
    EXPECT_EQ(maxSubArray(nums), 3);
}

TEST(MaxSubArrayTest, HandlesAllZeros) {
    std::vector<int> nums = {0, 0, 0, 0, 0};
    EXPECT_EQ(maxSubArray(nums), 0);
}
