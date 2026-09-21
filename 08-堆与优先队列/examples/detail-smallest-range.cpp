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

optional<pair<int, int>> smallestCoveringRange(const vector<vector<int>>& lists) {
    if (lists.empty()) return nullopt;
    using Entry = tuple<int, size_t, size_t>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pending;
    int currentMax = INT_MIN;
    for (size_t row = 0; row < lists.size(); ++row) {
        if (lists[row].empty()) return nullopt;
        pending.emplace(lists[row][0], row, 0);
        currentMax = max(currentMax, lists[row][0]);
    }
    int bestLeft = get<0>(pending.top()), bestRight = currentMax;
    while (true) {
        auto [currentMin, row, index] = pending.top(); pending.pop();
        long long width = (long long)currentMax - currentMin;
        long long bestWidth = (long long)bestRight - bestLeft;
        if (width < bestWidth || (width == bestWidth && currentMin < bestLeft)) {
            bestLeft = currentMin; bestRight = currentMax;
        }
        if (index + 1 == lists[row].size()) break;
        int next = lists[row][index + 1];
        currentMax = max(currentMax, next);
        pending.emplace(next, row, index + 1);
    }
    return pair<int, int>{bestLeft, bestRight};
}
