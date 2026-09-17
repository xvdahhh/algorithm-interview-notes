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

int coinChangeMemo(const vector<int>& coins, int amount) {
    if (amount<0) return -1;
    const int INF=INT_MAX/2;
    vector<int> memo(amount+1,-1);
    function<int(int)> dfs=[&](int rem) {
        if (rem==0) return 0;
        if (memo[rem]!=-1) return memo[rem];
        int best=INF;
        for (int c:coins) {
            if (c<=0) throw invalid_argument("positive coins required");
            if (c<=rem) best=min(best,1+dfs(rem-c));
        }
        return memo[rem]=best;
    };
    int ans=dfs(amount);
    return ans==INF ? -1 : ans;
}
