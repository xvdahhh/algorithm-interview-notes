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

class RandomizedMultisetExample {
    vector<int> data;
    unordered_map<int,unordered_set<size_t>> positions;
    mt19937 rng;
public:
    explicit RandomizedMultisetExample(uint32_t seed = 5489U): rng(seed) {}
    bool insert(int x) {
        auto& places = positions[x];
        bool newValue = places.empty();
        places.insert(data.size()); data.push_back(x); return newValue;
    }
    bool eraseOne(int x) {
        auto it = positions.find(x);
        if (it == positions.end()) return false;
        size_t index = *it->second.begin(), lastIndex = data.size()-1;
        int lastValue = data.back();
        it->second.erase(index);
        if (index != lastIndex) {
            data[index] = lastValue;
            auto& lastPlaces = positions.at(lastValue);
            lastPlaces.erase(lastIndex); lastPlaces.insert(index);
        }
        data.pop_back();
        if (it->second.empty()) positions.erase(it);
        return true;
    }
    optional<int> getRandom() {
        if (data.empty()) return nullopt;
        uniform_int_distribution<size_t> choose(0,data.size()-1);
        return data[choose(rng)];
    }
    size_t count(int x) const {
        auto it = positions.find(x);
        return it == positions.end() ? 0 : it->second.size();
    }
    size_t size() const { return data.size(); }
};
