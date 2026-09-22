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

class ReservoirSample {
    size_t capacity;
    uint64_t seen = 0;
    vector<int> samples;
    mt19937 rng;
public:
    ReservoirSample(int k, uint32_t seed = 5489U): rng(seed) {
        if (k < 0) throw invalid_argument("k");
        capacity = (size_t)k;
    }
    void offer(int value) {
        if (seen == UINT64_MAX) throw overflow_error("stream length");
        ++seen;
        if (samples.size() < capacity) samples.push_back(value);
        else if (capacity > 0) {
            uniform_int_distribution<uint64_t> choose(0,seen-1);
            uint64_t index = choose(rng);
            if (index < capacity) samples[(size_t)index] = value;
        }
    }
    vector<int> snapshot() const { return samples; }
    uint64_t processed() const { return seen; }
};
