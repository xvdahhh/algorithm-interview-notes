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

vector<int> topoSort(const vector<vector<int>>& g) {
    int n=(int)g.size();
    vector<int> degree(n,0), order;
    for (const auto& edges:g) for (int v:edges) ++degree[v];
    queue<int> q;
    for (int u=0;u<n;++u) if (degree[u]==0) q.push(u);
    while (!q.empty()) {
        int u=q.front(); q.pop(); order.push_back(u);
        for (int v:g[u]) if (--degree[v]==0) q.push(v);
    }
    if ((int)order.size()!=n) return {}; // 非空图时，空结果表示有环
    return order;
}
