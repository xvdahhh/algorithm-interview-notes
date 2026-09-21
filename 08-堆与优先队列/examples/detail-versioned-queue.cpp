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

class VersionedMinQueue {
    struct State { int priority; uint64_t version; };
    using Entry = tuple<int, int, uint64_t>; // priority, id, version
    priority_queue<Entry, vector<Entry>, greater<Entry>> heap;
    unordered_map<int, State> live;
    uint64_t nextVersion = 0;
    void prune() {
        while (!heap.empty()) {
            auto [priority, id, version] = heap.top();
            auto it = live.find(id);
            if (it != live.end() && it->second.version == version) break;
            heap.pop();
        }
    }
public:
    void put(int id, int priority) {
        if (nextVersion == UINT64_MAX) throw overflow_error("version exhausted");
        uint64_t version = ++nextVersion;
        heap.emplace(priority, id, version);
        live[id] = {priority, version};
    }
    void cancel(int id) { live.erase(id); }
    optional<pair<int, int>> pop() {
        prune();
        if (heap.empty()) return nullopt;
        auto [priority, id, version] = heap.top();
        heap.pop(); live.erase(id);
        return pair<int, int>{id, priority};
    }
};
