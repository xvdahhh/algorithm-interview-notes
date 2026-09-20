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

int minimumEatingSpeed(const vector<int>& piles, long long hours) {
    if (piles.empty()) return 0;
    if (hours <= 0) throw invalid_argument("hours must be positive");
    int hi = 0;
    for (int value : piles) {
        if (value <= 0) throw invalid_argument("piles must be positive");
        hi = max(hi, value);
    }
    if (hours < (long long)piles.size()) return -1;
    auto feasible = [&](int speed) {
        long long used = 0;
        for (int value : piles) {
            used += value / speed + (value % speed != 0);
            if (used > hours) return false;
        }
        return true;
    };
    int lo = 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
