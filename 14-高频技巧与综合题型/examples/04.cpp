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

vector<int> primesUpTo(int n){
    if(n<2) return {};
    vector<bool> prime(n+1,true);
    prime[0]=prime[1]=false;
    for(int p=2;p<=n/p;++p)
        if(prime[p])
            for(long long x=1LL*p*p;x<=n;x+=p) prime[(size_t)x]=false;
    vector<int> ans;
    for(int x=2;x<=n;++x) if(prime[x]) ans.push_back(x);
    return ans;
}
long long gcdNonnegative(long long a,long long b){
    // 前提：a,b >= 0；约定 gcd(0,0)=0。
    while(b){ long long r=a%b; a=b; b=r; }
    return a;
}
