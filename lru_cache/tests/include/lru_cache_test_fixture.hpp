#pragma once
#include <gtest/gtest.h>
#include <memory>
#include "lru_cache.hpp"

class LRUCacheTest : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        // Most cache behavior tests use capacity two to force eviction quickly.
        cache = std::make_unique<LRUCache<int, int>>(2);
    }
    std::unique_ptr<LRUCache<int, int>> cache;
};
