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

long long knapsack01(const vector<int>& weight,
                     const vector<int>& value,int capacity) {
    if(capacity<0 || weight.size()!=value.size())
        throw invalid_argument("invalid input");
    vector<long long> dp(capacity+1,0);
    for(int i=0;i<(int)weight.size();++i){
        if(weight[i]<=0) throw invalid_argument("positive weights required");
        for(int c=capacity;c>=weight[i];--c)
            dp[c]=max(dp[c],dp[c-weight[i]]+value[i]);
    }
    return dp[capacity];
}
