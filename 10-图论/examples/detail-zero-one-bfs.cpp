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

vector<long long> zeroOneDistances(
    const vector<vector<pair<int,int>>>& g, int s) {
    const long long INF = LLONG_MAX / 4;
    int n = (int)g.size();
    if (s < 0 || s >= n) throw out_of_range("source");
    for (const auto& row : g) for (auto [v,w] : row) {
        if (v < 0 || v >= n) throw out_of_range("edge");
        if (w != 0 && w != 1) throw invalid_argument("not a 0/1 edge");
    }
    vector<long long> d(n, INF);
    deque<pair<long long,int>> q;
    d[s] = 0; q.push_front({0,s});
    while (!q.empty()) {
        auto [du,u] = q.front(); q.pop_front();
        if (du != d[u]) continue;
        for (auto [v,w] : g[u]) if (du + w < d[v]) {
            d[v] = du + w;
            if (w == 0) q.push_front({d[v],v});
            else q.push_back({d[v],v});
        }
    }
    return d;
}
