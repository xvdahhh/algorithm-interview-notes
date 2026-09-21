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

optional<int> minimumIntervalCover(
    vector<pair<int,int>> intervals, int left, int right) {
    if (left > right) throw invalid_argument("target");
    for (auto [l,r] : intervals) if (l >= r) throw invalid_argument("interval");
    if (left == right) return 0;
    sort(intervals.begin(),intervals.end());
    int frontier = left, used = 0;
    size_t i = 0;
    while (frontier < right) {
        int next = frontier;
        while (i < intervals.size() && intervals[i].first <= frontier) {
            next = max(next,intervals[i].second); ++i;
        }
        if (next == frontier) return nullopt;
        frontier = next; ++used;
    }
    return used;
}
