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

optional<vector<long long>> dagDistances(
    const vector<vector<pair<int,int>>>& g, int s) {
    int n = (int)g.size();
    if (n < 1 || n > 1000000 || s < 0 || s >= n) throw invalid_argument("size/source");
    vector<int> indegree(n);
    for (const auto& row : g) for (auto [v,w] : row) {
        if (v < 0 || v >= n) throw out_of_range("edge");
        if (w < -1000000000 || w > 1000000000) throw invalid_argument("weight");
        ++indegree[v];
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) if (!indegree[i]) q.push(i);
    const long long INF = LLONG_MAX / 4;
    vector<long long> d(n, INF); d[s] = 0;
    int processed = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop(); ++processed;
        for (auto [v,w] : g[u]) {
            if (d[u] != INF) d[v] = min(d[v], d[u] + w);
            if (--indegree[v] == 0) q.push(v);
        }
    }
    if (processed != n) return nullopt;
    return d;
}
