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

vector<pair<int, int>> smallestPairs(const vector<int>& a, const vector<int>& b, int k) {
    if (k < 0) throw invalid_argument("negative k");
    if (k == 0 || a.empty() || b.empty()) return {};
    using Entry = tuple<long long, size_t, size_t>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pending;
    size_t initial = min((size_t)k, a.size());
    for (size_t i = 0; i < initial; ++i) pending.emplace((long long)a[i] + b[0], i, 0);
    vector<pair<int, int>> result;
    while (!pending.empty() && result.size() < (size_t)k) {
        auto [sum, i, j] = pending.top(); pending.pop();
        result.push_back({a[i], b[j]});
        if (j + 1 < b.size()) pending.emplace((long long)a[i] + b[j + 1], i, j + 1);
    }
    return result;
}
