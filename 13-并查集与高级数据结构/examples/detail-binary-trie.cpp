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

class BinaryTrie32 {
    struct Node { array<int,2> next{{-1,-1}}; };
    vector<Node> nodes{Node{}};
    bool nonempty = false;
public:
    void insert(uint32_t x) {
        int u = 0;
        for (int bit = 31; bit >= 0; --bit) {
            int b = (x >> bit) & 1U;
            if (nodes[u].next[b] == -1) {
                int v = (int)nodes.size(); nodes.emplace_back();
                nodes[u].next[b] = v;
            }
            u = nodes[u].next[b];
        }
        nonempty = true;
    }
    optional<uint32_t> maxXor(uint32_t x) const {
        if (!nonempty) return nullopt;
        int u = 0; uint32_t answer = 0;
        for (int bit = 31; bit >= 0; --bit) {
            int b = (x >> bit) & 1U;
            if (nodes[u].next[b^1] != -1) {
                answer |= uint32_t(1) << bit; u = nodes[u].next[b^1];
            } else u = nodes[u].next[b];
        }
        return answer;
    }
};
