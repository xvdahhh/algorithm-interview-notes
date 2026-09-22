#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

class LFUCacheExample {
    struct Entry { int value; uint64_t frequency; list<int>::iterator where; };
    size_t capacity;
    uint64_t minimum = 0;
    unordered_map<int,Entry> entries;
    unordered_map<uint64_t,list<int>> buckets;
    void touch(int key) {
        auto& entry = entries.at(key);
        uint64_t old = entry.frequency;
        if (old == UINT64_MAX) throw overflow_error("frequency");
        auto bucket = buckets.find(old);
        bucket->second.erase(entry.where);
        if (bucket->second.empty()) {
            buckets.erase(bucket);
            if (minimum == old) minimum = old+1;
        }
        entry.frequency = old+1;
        auto& target = buckets[old+1];
        target.push_front(key); entry.where = target.begin();
    }
public:
    explicit LFUCacheExample(int cap) {
        if (cap < 0) throw invalid_argument("capacity");
        capacity = (size_t)cap;
    }
    LFUCacheExample(const LFUCacheExample&) = delete;
    LFUCacheExample& operator=(const LFUCacheExample&) = delete;
    optional<int> get(int key) {
        auto it = entries.find(key);
        if (it == entries.end()) return nullopt;
        int result = it->second.value; touch(key); return result;
    }
    void put(int key, int value) {
        auto it = entries.find(key);
        if (it != entries.end()) {
            touch(key); entries.at(key).value = value; return;
        }
        if (!capacity) return;
        if (entries.size() == capacity) {
            auto bucket = buckets.find(minimum);
            int victim = bucket->second.back();
            bucket->second.pop_back(); entries.erase(victim);
            if (bucket->second.empty()) buckets.erase(bucket);
        }
        auto& bucket = buckets[1]; bucket.push_front(key);
        entries.emplace(key,Entry{value,1,bucket.begin()}); minimum = 1;
    }
    size_t size() const { return entries.size(); }
};
