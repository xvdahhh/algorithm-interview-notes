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

long long minMergeCost(const vector<int>& weights) {
    priority_queue<long long,vector<long long>,greater<long long>> pq;
    for(int x:weights){
        if(x<0) throw invalid_argument("nonnegative weights required");
        pq.push(x);
    }
    long long cost=0;
    while(pq.size()>1){
        long long a=pq.top(); pq.pop();
        long long b=pq.top(); pq.pop();
        cost+=a+b; pq.push(a+b);
    }
    return cost;
}
