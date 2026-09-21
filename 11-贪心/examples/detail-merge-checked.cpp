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

long long optimalMergeChecked(const vector<long long>& weights) {
    priority_queue<long long,vector<long long>,greater<long long>> pq;
    for (long long x : weights) {
        if (x < 0) throw invalid_argument("nonnegative weights required");
        pq.push(x);
    }
    long long cost = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        if (a > LLONG_MAX-b) throw overflow_error("merged weight");
        long long merged = a+b;
        if (cost > LLONG_MAX-merged) throw overflow_error("total cost");
        cost += merged; pq.push(merged);
    }
    return cost;
}
