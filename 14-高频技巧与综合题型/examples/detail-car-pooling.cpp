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

bool canCarPool(const vector<array<int,3>>& trips, long long capacity) {
    if (capacity < 0 || trips.size() > 1000000) throw invalid_argument("capacity/size");
    vector<pair<int,long long>> events;
    for (auto trip : trips) {
        int passengers = trip[0], start = trip[1], end = trip[2];
        if (passengers < 0 || start > end) throw invalid_argument("trip");
        if (start == end || passengers == 0) continue;
        events.push_back({start,passengers});
        events.push_back({end,-(long long)passengers});
    }
    sort(events.begin(),events.end());
    long long active = 0; size_t i = 0;
    while (i < events.size()) {
        int time = events[i].first;
        while (i < events.size() && events[i].first == time) active += events[i++].second;
        if (active > capacity) return false;
    }
    return true;
}
