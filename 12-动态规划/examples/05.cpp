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

int longestPalindromeSubseq(const string& s) {
    int n=(int)s.size();
    if(n==0) return 0;
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int i=0;i<n;++i) dp[i][i]=1;
    for(int len=2;len<=n;++len)
        for(int l=0;l+len<=n;++l){
            int r=l+len-1;
            if(s[l]==s[r]) dp[l][r]=2+(len==2 ? 0 : dp[l+1][r-1]);
            else dp[l][r]=max(dp[l+1][r],dp[l][r-1]);
        }
    return dp[0][n-1];
}
