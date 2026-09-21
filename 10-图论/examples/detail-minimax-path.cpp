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

optional<long long> minimumBottleneck(
    const vector<vector<pair<int,int>>>& g, int s, int t) {
    int n = (int)g.size();
    if (s < 0 || s >= n || t < 0 || t >= n) throw out_of_range("vertex");
    for (const auto& row : g) for (auto [v,w] : row) {
        if (v < 0 || v >= n) throw out_of_range("edge");
        if (w < 0) throw invalid_argument("negative weight");
    }
    const long long INF = LLONG_MAX / 4;
    vector<long long> d(n, INF);
    using State = pair<long long,int>;
    priority_queue<State,vector<State>,greater<State>> pq;
    d[s] = 0; pq.push({0,s});
    while (!pq.empty()) {
        auto [du,u] = pq.top(); pq.pop();
        if (du != d[u]) continue;
        if (u == t) return du;
        for (auto [v,w] : g[u]) {
            long long candidate = max(du, (long long)w);
            if (candidate < d[v]) { d[v] = candidate; pq.push({d[v],v}); }
        }
    }
    return nullopt;
}
