#pragma once

#include "factory.hpp"
#include <gtest/gtest.h>

namespace utils {

class FactoryTest : public ::testing::Test {
protected:
	Factory factory;
};

} // namespace utils

