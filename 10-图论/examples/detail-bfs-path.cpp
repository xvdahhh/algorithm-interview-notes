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

optional<vector<int>> shortestUnweightedPath(
    const vector<vector<int>>& g, int s, int t) {
    int n = (int)g.size();
    if (s < 0 || s >= n || t < 0 || t >= n)
        throw out_of_range("vertex");
    vector<int> dist(n, -1), parent(n, -1);
    queue<int> q;
    dist[s] = 0; q.push(s);
    while (!q.empty() && dist[t] == -1) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (dist[v] == -1) {
            dist[v] = dist[u] + 1;
            parent[v] = u;
            q.push(v);
        }
    }
    if (dist[t] == -1) return nullopt;
    vector<int> path;
    for (int v = t; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
