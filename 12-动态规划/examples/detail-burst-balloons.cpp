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

long long burstBalloonsDP(const vector<int>& nums) {
    if (nums.size() > 300) throw invalid_argument("teaching size limit");
    vector<long long> a{1};
    for (int x : nums) {
        if (x < 0 || x > 1000) throw invalid_argument("balloon value");
        a.push_back(x);
    }
    a.push_back(1);
    int n = (int)a.size();
    vector<vector<long long>> dp(n,vector<long long>(n));
    for (int gap = 2; gap < n; ++gap)
        for (int l = 0; l+gap < n; ++l) {
            int r = l+gap;
            for (int k = l+1; k < r; ++k)
                dp[l][r] = max(dp[l][r],dp[l][k]+dp[k][r]+a[l]*a[k]*a[r]);
        }
    return dp[0][n-1];
}
