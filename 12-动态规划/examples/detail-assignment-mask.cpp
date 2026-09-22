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

pair<long long,vector<int>> minimumAssignment(const vector<vector<int>>& cost) {
    int n = (int)cost.size();
    if (n > 18) throw invalid_argument("n <= 18 required");
    for (const auto& row : cost) {
        if ((int)row.size() != n) throw invalid_argument("square matrix");
        for (int x : row) if (x < -1000000000 || x > 1000000000)
            throw invalid_argument("cost");
    }
    int total = 1 << n;
    const long long INF = LLONG_MAX/4;
    vector<long long> dp(total,INF);
    vector<int> chosen(total,-1);
    dp[0] = 0;
    for (int mask = 0; mask < total; ++mask) {
        int worker = 0;
        for (int bits = mask; bits; bits &= bits-1) ++worker;
        if (worker == n || dp[mask] == INF) continue;
        for (int task = 0; task < n; ++task) if (!(mask & (1 << task))) {
            int next = mask | (1 << task);
            long long candidate = dp[mask]+cost[worker][task];
            if (candidate < dp[next]) { dp[next] = candidate; chosen[next] = task; }
        }
    }
    vector<int> assignment(n);
    int mask = total-1;
    for (int worker = n-1; worker >= 0; --worker) {
        int task = chosen[mask];
        assignment[worker] = task; mask ^= 1 << task;
    }
    return {dp.back(),assignment};
}
