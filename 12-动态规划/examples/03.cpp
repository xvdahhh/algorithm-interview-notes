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

long long coinCombinations(const vector<int>& coins,int amount) {
    if(amount<0) return 0;
    vector<long long> dp(amount+1,0);
    dp[0]=1;
    for(int c:coins){
        if(c<=0) throw invalid_argument("positive distinct coins required");
        for(int s=c;s<=amount;++s) dp[s]+=dp[s-c];
    }
    return dp[amount];
}
