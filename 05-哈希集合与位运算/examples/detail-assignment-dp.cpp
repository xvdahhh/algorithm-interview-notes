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

long long minimumAssignmentCost(const vector<vector<int>>& cost) {
    int n = (int)cost.size();
    if (n > 20) throw invalid_argument("n must not exceed 20");
    for (const auto& row : cost) {
        if ((int)row.size() != n) throw invalid_argument("square matrix required");
        for (int value : row)
            if (value < 0 || value > 1000000000)
                throw invalid_argument("cost outside supported range");
    }
    size_t total = size_t{1} << n;
    const long long INF = LLONG_MAX / 4;
    vector<long long> dp(total, INF);
    dp[0] = 0;
    for (size_t mask = 0; mask < total; ++mask) {
        int person = 0;
        for (size_t bits = mask; bits != 0; bits &= bits - 1) ++person;
        if (person == n || dp[mask] == INF) continue;
        for (int job = 0; job < n; ++job) {
            size_t bit = size_t{1} << job;
            if ((mask & bit) != 0) continue;
            size_t next = mask | bit;
            dp[next] = min(dp[next], dp[mask] + cost[person][job]);
        }
    }
    return dp.back();
}
