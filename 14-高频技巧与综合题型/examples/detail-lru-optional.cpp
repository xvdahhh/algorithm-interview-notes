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

class OptionalLRU {
    size_t capacity;
    list<pair<int,int>> order;
    unordered_map<int,list<pair<int,int>>::iterator> position;
    void trim() {
        while (order.size() > capacity) {
            position.erase(order.back().first); order.pop_back();
        }
    }
public:
    explicit OptionalLRU(int cap) {
        if (cap < 0) throw invalid_argument("capacity");
        capacity = (size_t)cap;
    }
    OptionalLRU(const OptionalLRU&) = delete;
    OptionalLRU& operator=(const OptionalLRU&) = delete;
    optional<int> get(int key) {
        auto it = position.find(key);
        if (it == position.end()) return nullopt;
        order.splice(order.begin(),order,it->second);
        return it->second->second;
    }
    void put(int key, int value) {
        auto it = position.find(key);
        if (it != position.end()) {
            it->second->second = value;
            order.splice(order.begin(),order,it->second); return;
        }
        if (!capacity) return;
        order.emplace_front(key,value); position[key] = order.begin(); trim();
    }
    bool erase(int key) {
        auto it = position.find(key);
        if (it == position.end()) return false;
        order.erase(it->second); position.erase(it); return true;
    }
    void resize(int cap) {
        if (cap < 0) throw invalid_argument("capacity");
        capacity = (size_t)cap; trim();
    }
    size_t size() const { return order.size(); }
};
