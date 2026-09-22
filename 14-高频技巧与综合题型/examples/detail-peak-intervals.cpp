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

struct PeakConcurrency {
    int count = 0;
    vector<pair<int,int>> spans;
};
PeakConcurrency peakConcurrency(const vector<pair<int,int>>& intervals) {
    vector<pair<int,int>> events;
    for (auto [l,r] : intervals) {
        if (l > r) throw invalid_argument("interval");
        if (l == r) continue;
        events.push_back({l,1}); events.push_back({r,-1});
    }
    sort(events.begin(),events.end());
    PeakConcurrency result; int active = 0;
    size_t i = 0;
    while (i < events.size()) {
        int time = events[i].first;
        while (i < events.size() && events[i].first == time) active += events[i++].second;
        if (i == events.size()) break;
        int next = events[i].first;
        if (active > result.count) { result.count = active; result.spans.clear(); }
        if (active > 0 && active == result.count) {
            if (!result.spans.empty() && result.spans.back().second == time)
                result.spans.back().second = next;
            else result.spans.push_back({time,next});
        }
    }
    return result;
}
