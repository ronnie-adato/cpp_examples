# LRU Cache (LeetCode 146, Medium)

LeetCode: <https://leetcode.com/problems/lru-cache/>

## Problem Description

Design a least recently used cache with a positive capacity.

The cache should support the following operations in `O(1)` average time:

- `get(key)`: Return the value for `key` if it exists, otherwise report a miss.
- `put(key, value)`: Sets or inserts the value if the key is not already present. When the cache
  reaches its capacity, evict the least recently used item before inserting a new item.

## Requirements

- The constructor should accept the cache’s capacity.
- Use appropriate STL containers.
- Thread safety is not required, but code clarity matters.
- This implementation reports a cache miss by throwing `std::out_of_range`.

## Example Usage

```cpp
LRUCache cache(2); // capacity = 2
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);    // returns 1
cache.put(3, 3); // evicts key 2
try {
  cache.get(2); // throws exception (not found)
} catch (const std::out_of_range&) {}
cache.put(4, 4); // evicts key 1
try {
  cache.get(1); // throws exception (not found)
} catch (const std::out_of_range&) {}
cache.get(3);    // returns 3
cache.get(4);    // returns 4
```
