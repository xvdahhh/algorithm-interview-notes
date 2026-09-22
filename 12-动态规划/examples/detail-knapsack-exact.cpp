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

optional<long long> knapsackExact(const vector<int>& weight,
                                  const vector<int>& value, int capacity) {
    if (capacity < 0 || capacity > 200000 || weight.size() != value.size())
        throw invalid_argument("capacity/length");
    vector<optional<long long>> dp(capacity+1);
    dp[0] = 0;
    for (int i = 0; i < (int)weight.size(); ++i) {
        if (weight[i] <= 0) throw invalid_argument("positive weight");
        for (int c = capacity; c >= weight[i]; --c) {
            if (!dp[c-weight[i]]) continue;
            long long candidate = *dp[c-weight[i]]+value[i];
            if (!dp[c] || candidate > *dp[c]) dp[c] = candidate;
        }
    }
    return dp[capacity];
}
