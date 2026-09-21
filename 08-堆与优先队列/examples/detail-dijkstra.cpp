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

struct WeightedEdge { int to; int weight; };
vector<optional<long long>> shortestDistances(
    const vector<vector<WeightedEdge>>& graph, int source) {
    if (graph.size() > 100000) throw invalid_argument("too many vertices");
    int n = (int)graph.size();
    if (source < 0 || source >= n) throw out_of_range("invalid source");
    for (const auto& edges : graph)
        for (const auto& edge : edges)
            if (edge.to < 0 || edge.to >= n || edge.weight < 0 ||
                edge.weight > 1000000000)
                throw invalid_argument("invalid edge");
    const long long INF = LLONG_MAX / 4;
    vector<long long> distance(n, INF);
    using Entry = pair<long long, int>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pending;
    distance[source] = 0; pending.push({0, source});
    while (!pending.empty()) {
        auto [value, u] = pending.top(); pending.pop();
        if (value != distance[u]) continue;
        for (const auto& edge : graph[u]) {
            long long candidate = value + edge.weight;
            if (candidate < distance[edge.to]) {
                distance[edge.to] = candidate;
                pending.push({candidate, edge.to});
            }
        }
    }
    vector<optional<long long>> result(n);
    for (int i = 0; i < n; ++i)
        if (distance[i] != INF) result[i] = distance[i];
    return result;
}
