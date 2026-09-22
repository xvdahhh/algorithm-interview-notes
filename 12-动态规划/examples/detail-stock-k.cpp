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

long long stockAtMostK(const vector<int>& prices, int k) {
    if (k < 0) throw invalid_argument("k");
    for (int p : prices) if (p < 0) throw invalid_argument("price");
    int n = (int)prices.size();
    if (k >= n/2) {
        long long answer = 0;
        for (int i = 1; i < n; ++i)
            answer += max(0LL,(long long)prices[i]-prices[i-1]);
        return answer;
    }
    const long long NEG = LLONG_MIN/4;
    vector<long long> cash(k+1,0), hold(k+1,NEG);
    for (int p : prices) {
        auto oldCash = cash, oldHold = hold;
        for (int t = 1; t <= k; ++t) {
            hold[t] = max(oldHold[t],oldCash[t-1]-p);
            cash[t] = oldCash[t];
            if (oldHold[t] != NEG) cash[t] = max(cash[t],oldHold[t]+p);
        }
    }
    return cash[k];
}
