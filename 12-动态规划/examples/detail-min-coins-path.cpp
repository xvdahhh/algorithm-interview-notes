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

optional<vector<int>> minimumCoinsPath(vector<int> coins, int amount) {
    if (amount < 0 || amount > 200000) throw invalid_argument("amount");
    for (int c : coins) if (c <= 0) throw invalid_argument("positive coin");
    sort(coins.begin(),coins.end());
    coins.erase(unique(coins.begin(),coins.end()),coins.end());
    const int INF = amount+1;
    vector<int> dp(amount+1,INF), last(amount+1,-1);
    dp[0] = 0;
    for (int s = 1; s <= amount; ++s)
        for (int c : coins) {
            if (c > s) break;
            if (dp[s-c] != INF && dp[s-c]+1 < dp[s]) {
                dp[s] = dp[s-c]+1; last[s] = c;
            }
        }
    if (dp[amount] == INF) return nullopt;
    vector<int> chosen;
    for (int s = amount; s > 0; s -= last[s]) chosen.push_back(last[s]);
    return chosen;
}
