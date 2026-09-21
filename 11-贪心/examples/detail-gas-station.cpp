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

optional<int> gasStationStart(const vector<int>& gas, const vector<int>& cost) {
    if (gas.size() != cost.size()) throw invalid_argument("length");
    if (gas.empty()) return nullopt;
    long long total = 0, tank = 0;
    int start = 0;
    for (int i = 0; i < (int)gas.size(); ++i) {
        if (gas[i] < 0 || cost[i] < 0) throw invalid_argument("negative value");
        long long delta = (long long)gas[i]-cost[i];
        total += delta; tank += delta;
        if (tank < 0) { start = i+1; tank = 0; }
    }
    if (total < 0) return nullopt;
    return start;
}
