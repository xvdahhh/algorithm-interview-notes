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

long long adjacentMergeCost(const vector<int>& a) {
    int n = (int)a.size();
    if (n > 300) throw invalid_argument("teaching size limit");
    vector<long long> prefix(n+1);
    for (int i = 0; i < n; ++i) {
        if (a[i] < 0 || a[i] > 1000000000) throw invalid_argument("weight");
        prefix[i+1] = prefix[i]+a[i];
    }
    if (n <= 1) return 0;
    const long long INF = LLONG_MAX/4;
    vector<vector<long long>> dp(n,vector<long long>(n,0));
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l+len <= n; ++l) {
            int r = l+len-1; dp[l][r] = INF;
            for (int k = l; k < r; ++k)
                dp[l][r] = min(dp[l][r],dp[l][k]+dp[k+1][r]+prefix[r+1]-prefix[l]);
        }
    }
    return dp[0][n-1];
}
