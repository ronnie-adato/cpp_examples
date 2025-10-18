#include "utils_test_fixture.hpp"

TEST_F(JoinTest, EmptyVectorReturnsEmptyString) {
    std::vector<std::string> v;
    EXPECT_EQ(join_vec(v), "");
}

TEST_F(JoinTest, SingleElementReturnsElement) {
    std::vector<std::string> v = {"hello"};
    EXPECT_EQ(join_vec(v), "hello");
}

TEST_F(JoinTest, TwoElementsJoinedWithSpace) {
    std::vector<std::string> v = {"hello", "world"};
    EXPECT_EQ(join_vec(v), "hello world");
}

TEST_F(JoinTest, MultipleElementsJoinedWithSpace) {
    std::vector<std::string> v = {"a", "b", "c", "d"};
    EXPECT_EQ(join_vec(v), "a b c d");
}

TEST_F(JoinTest, ElementsWithSpaces) {
    std::vector<std::string> v = {"foo bar", "baz"};
    EXPECT_EQ(join_vec(v), "foo bar baz");
}
