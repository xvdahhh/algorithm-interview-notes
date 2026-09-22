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

struct RankedCandidate { string name; int score; int id; };
struct BetterCandidate {
    bool operator()(const RankedCandidate& a, const RankedCandidate& b) const {
        if (a.score != b.score) return a.score > b.score;
        if (a.name != b.name) return a.name < b.name;
        return a.id < b.id;
    }
};
struct LowerPriority {
    bool operator()(const RankedCandidate& a, const RankedCandidate& b) const {
        return BetterCandidate{}(b, a);
    }
};
vector<RankedCandidate> bestCandidates(const vector<RankedCandidate>& a, size_t k) {
    priority_queue<RankedCandidate, vector<RankedCandidate>, LowerPriority> pq;
    for (const auto& item : a) pq.push(item);
    vector<RankedCandidate> result;
    while (!pq.empty() && result.size() < k) {
        result.push_back(pq.top());
        pq.pop();
    }
    return result;
}
