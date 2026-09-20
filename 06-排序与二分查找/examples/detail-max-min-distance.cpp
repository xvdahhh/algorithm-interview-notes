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

long long maximumMinimumDistance(vector<int> positions, int count) {
    int n = (int)positions.size();
    if (count < 2 || count > n) throw invalid_argument("require 2 <= count <= n");
    sort(positions.begin(), positions.end());
    auto feasible = [&](long long distance) {
        int placed = 1;
        long long last = positions[0];
        for (int i = 1; i < n; ++i) {
            if ((long long)positions[i] - last >= distance) {
                last = positions[i];
                if (++placed == count) return true;
            }
        }
        return false;
    };
    long long lo = 0, hi = (long long)positions.back() - positions.front();
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
