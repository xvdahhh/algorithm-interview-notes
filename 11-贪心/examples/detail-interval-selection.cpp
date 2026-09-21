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

vector<int> selectIntervals(const vector<pair<int,int>>& intervals) {
    vector<tuple<int,int,int>> order; // (右端点, 左端点, 原下标)
    for (int i = 0; i < (int)intervals.size(); ++i) {
        auto [l,r] = intervals[i];
        if (l >= r) throw invalid_argument("positive-length interval required");
        order.push_back({r,l,i});
    }
    sort(order.begin(),order.end());
    long long end = LLONG_MIN;
    vector<int> chosen;
    for (auto [r,l,id] : order) if (l >= end) {
        chosen.push_back(id); end = r;
    }
    return chosen;
}
