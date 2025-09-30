# LRU Cache Implementation

## Task

Implement a Least Recently Used (LRU) cache class in C++.

## Problem Description
The LRU cache should support the following operations in O(1) time complexity:

- `get(key)`: Returns the value of the key if the key exists in the cache, otherwise throws an exception.
- `put(key, value)`: Sets or inserts the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least recently used item before inserting a new item.

## Requirements
- The constructor should accept the cache’s capacity.
- Use appropriate STL containers.
- Thread safety is not required, but code clarity matters.

Example Usage

```cpp
LRUCache cache(2); // capacity = 2
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);    // returns 1
cache.put(3, 3); // evicts key 2
try {
	cache.get(2);    // throws exception (not found)
} catch (const std::out_of_range&) {}
cache.put(4, 4); // evicts key 1
try {
	cache.get(1);    // throws exception (not found)
} catch (const std::out_of_range&) {}
cache.get(3);    // returns 3
cache.get(4);    // returns 4
```
