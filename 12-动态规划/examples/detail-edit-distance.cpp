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

int editDistanceRolling(const string& source, const string& target) {
    // 让列是短串。单位插删改的距离对称，所以可交换两串。
    const string* a = &source;
    const string* b = &target;
    if (a->size() < b->size()) swap(a,b);
    int n = (int)a->size(), m = (int)b->size();
    vector<int> dp(m+1);
    iota(dp.begin(),dp.end(),0);
    for (int i = 1; i <= n; ++i) {
        int diagonal = dp[0];
        dp[0] = i;
        for (int j = 1; j <= m; ++j) {
            int above = dp[j];
            if ((*a)[i-1] == (*b)[j-1]) dp[j] = diagonal;
            else dp[j] = 1+min({above,dp[j-1],diagonal});
            diagonal = above;
        }
    }
    return dp[m];
}
