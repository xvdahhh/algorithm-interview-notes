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

struct BellmanResult {
    vector<long long> dist;
    vector<char> bad;
};
BellmanResult bellmanFordMarked(int n, const vector<tuple<int,int,int>>& edges, int s) {
    if (n < 1 || n > 1000000 || s < 0 || s >= n) throw invalid_argument("size/source");
    const long long INF = LLONG_MAX / 4;
    vector<vector<int>> g(n);
    for (auto [u,v,w] : edges) {
        if (u < 0 || u >= n || v < 0 || v >= n) throw out_of_range("edge");
        if (w < -1000000000 || w > 1000000000) throw invalid_argument("weight");
        g[u].push_back(v);
    }
    vector<long long> d(n, INF); d[s] = 0;
    for (int step = 1; step < n; ++step) {
        auto next = d;
        bool changed = false;
        for (auto [u,v,w] : edges) if (d[u] != INF && d[u] + w < next[v]) {
            next[v] = d[u] + w; changed = true;
        }
        d.swap(next);
        if (!changed) break;
    }
    vector<char> bad(n, false); queue<int> q;
    for (auto [u,v,w] : edges)
        if (d[u] != INF && d[u] + w < d[v] && !bad[v]) {
            bad[v] = true; q.push(v);
        }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (!bad[v]) { bad[v] = true; q.push(v); }
    }
    return {d,bad};
}
