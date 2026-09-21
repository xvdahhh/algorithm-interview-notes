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

struct SegmentSummary {
    long long sum, prefix, suffix, best;
};
SegmentSummary summarizeSegment(const vector<int>& a, int left, int right) {
    if (right - left == 1) {
        long long value = a[left];
        return {value, value, value, value};
    }
    int middle = left + (right - left) / 2;
    auto l = summarizeSegment(a, left, middle);
    auto r = summarizeSegment(a, middle, right);
    return {l.sum + r.sum,
            max(l.prefix, l.sum + r.prefix),
            max(r.suffix, r.sum + l.suffix),
            max({l.best, r.best, l.suffix + r.prefix})};
}
optional<long long> maximumSubarrayDivide(const vector<int>& a) {
    if (a.size() > 100000) throw invalid_argument("array too large");
    for (int value : a)
        if (value < -1000000000 || value > 1000000000)
            throw invalid_argument("value outside supported range");
    if (a.empty()) return nullopt;
    return summarizeSegment(a, 0, (int)a.size()).best;
}
