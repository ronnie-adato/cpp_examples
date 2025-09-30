#pragma once

#include <ng-log/logging.h>
#include <list>
#include <stdexcept>
#include <string>
#include <unordered_map>

template <typename K, typename V>

class LRUCache
{
   public:
    LRUCache(size_t capacity);
    V get(K key);
    void put(K key, V value);

   private:
    size_t capacity_;
    typedef std::pair<K, V> LIST_ELEM;
    std::list<LIST_ELEM> items_;
    std::unordered_map<K, typename std::list<LIST_ELEM>::iterator> cache_;
};

// Implementation
template <typename K, typename V>
LRUCache<K, V>::LRUCache(size_t capacity) : capacity_(capacity)
{
    LOG(INFO) << "LRUCache created with capacity: " << capacity_;
}

template <typename K, typename V>
V LRUCache<K, V>::get(K key)
{
    LOG(INFO) << "get(" << key << ") called";
    auto it = cache_.find(key);
    if (it == cache_.end())
    {
        LOG(INFO) << "Key " << key << " not found in cache";
        throw std::out_of_range(std::to_string(key) + " does not exist in the cache");
    }
    items_.splice(items_.begin(), items_, it->second);
    LOG(INFO) << "Key " << key << " accessed, value: " << it->second->second;
    return it->second->second;
}

template <typename K, typename V>
void LRUCache<K, V>::put(K key, V value)
{
    LOG(INFO) << "put(" << key << ", " << value << ") called";
    auto it = cache_.find(key);
    if (it == cache_.end())
    {
        if (items_.size() == capacity_)
        {
            LOG(INFO) << "Cache is full. Evicting least recently used key: " << items_.rbegin()->first;
            cache_.erase(items_.rbegin()->first);
            items_.pop_back();
        }
        items_.push_front(std::make_pair(key, value));
        cache_[key] = items_.begin();
        LOG(INFO) << "Inserted key: " << key << ", value: " << value;
    }
    else
    {
        it->second->second = value;
        items_.splice(items_.begin(), items_, it->second);
        LOG(INFO) << "Updated key: " << key << ", value: " << value;
    }
}
