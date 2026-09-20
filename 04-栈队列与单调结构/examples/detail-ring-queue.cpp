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

class RingQueue {
    vector<int> data;
    size_t head = 0, used = 0;
public:
    explicit RingQueue(int capacity) {
        if (capacity <= 0) throw invalid_argument("capacity must be positive");
        data.resize((size_t)capacity);
    }
    bool empty() const { return used == 0; }
    bool full() const { return used == data.size(); }
    bool push(int value) {
        if (full()) return false;
        data[(head + used) % data.size()] = value;
        ++used;
        return true;
    }
    optional<int> pop() {
        if (empty()) return nullopt;
        int value = data[head];
        head = (head + 1) % data.size();
        --used;
        return value;
    }
    optional<int> front() const {
        if (empty()) return nullopt;
        return data[head];
    }
};
