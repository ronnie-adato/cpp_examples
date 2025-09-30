
#include "lru_cache.hpp"
#include <gtest/gtest.h>
#include "../include/lru_cache_test_fixture.hpp"

TEST_F(LRUCacheTest, GetFromEmptyCacheThrows) {
	EXPECT_THROW(cache->get(1), std::out_of_range);
}

TEST_F(LRUCacheTest, PutAndGetSingleItem) {
	cache->put(1, 100);
	EXPECT_EQ(cache->get(1), 100);
}

TEST_F(LRUCacheTest, OverwriteValue) {
	cache->put(1, 100);
	cache->put(1, 200);
	EXPECT_EQ(cache->get(1), 200);
}

TEST_F(LRUCacheTest, EvictsLeastRecentlyUsed) {
	cache->put(1, 10);
	cache->put(2, 20);
	cache->put(3, 30); // should evict key 1
	EXPECT_THROW(cache->get(1), std::out_of_range);
	EXPECT_EQ(cache->get(2), 20);
	EXPECT_EQ(cache->get(3), 30);
}

TEST_F(LRUCacheTest, AccessUpdatesRecency) {
	cache->put(1, 10);
	cache->put(2, 20);
	cache->get(1); // 1 is now most recent
	cache->put(3, 30); // should evict key 2
	EXPECT_THROW(cache->get(2), std::out_of_range);
	EXPECT_EQ(cache->get(1), 10);
	EXPECT_EQ(cache->get(3), 30);
}

TEST_F(LRUCacheTest, PutUpdatesRecency) {
	cache->put(1, 10);
	cache->put(2, 20);
	cache->put(1, 15); // 1 is now most recent
	cache->put(3, 30); // should evict key 2
	EXPECT_THROW(cache->get(2), std::out_of_range);
	EXPECT_EQ(cache->get(1), 15);
	EXPECT_EQ(cache->get(3), 30);
}

TEST(LRUCacheSingleTest, CapacityOneEviction) {
	LRUCache<int, int> single(1);
	single.put(1, 1);
	single.put(2, 2);
	EXPECT_THROW(single.get(1), std::out_of_range);
	EXPECT_EQ(single.get(2), 2);
}

TEST(LRUCacheBigTest, LargeCapacityNoEviction) {
	LRUCache<int, int> big(100);
	for (int i = 0; i < 100; ++i) big.put(i, i * 10);
	for (int i = 0; i < 100; ++i) EXPECT_EQ(big.get(i), i * 10);
}

