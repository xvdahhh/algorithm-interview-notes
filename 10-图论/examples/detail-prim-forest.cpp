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

struct PrimForestResult {
    long long cost;
    int components;
    vector<pair<int,int>> edges;
};
PrimForestResult densePrimForest(const vector<vector<long long>>& weight) {
    const long long INF = LLONG_MAX / 4;
    int n = (int)weight.size();
    if (n > 1000000) throw invalid_argument("size");
    for (const auto& row : weight) if ((int)row.size() != n)
        throw invalid_argument("not square");
    for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
        long long w = weight[u][v];
        if (w != weight[v][u]) throw invalid_argument("not undirected");
        if (w != INF && (w < -1000000000LL || w > 1000000000LL))
            throw invalid_argument("weight");
    }
    vector<long long> key(n, INF);
    vector<int> parent(n, -1);
    vector<char> used(n, false);
    PrimForestResult result{0,0,{}};
    for (int step = 0; step < n; ++step) {
        int u = -1;
        for (int v = 0; v < n; ++v)
            if (!used[v] && (u == -1 || key[v] < key[u])) u = v;
        if (key[u] == INF) { key[u] = 0; ++result.components; }
        used[u] = true; result.cost += key[u];
        if (parent[u] != -1) result.edges.push_back({parent[u],u});
        for (int v = 0; v < n; ++v)
            if (!used[v] && weight[u][v] < key[v]) {
                key[v] = weight[u][v]; parent[v] = u;
            }
    }
    return result;
}
