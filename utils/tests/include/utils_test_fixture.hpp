#pragma once
#include "utils.hpp"
#include <gtest/gtest.h>

class JoinTest : public ::testing::Test {
protected:
    std::string join_vec(const std::vector<std::string>& v) {
        return utils::join(v);
    }
};
