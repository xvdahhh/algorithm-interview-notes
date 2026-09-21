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

struct TopologyResult {
    bool dag;
    bool unique;
    vector<int> order;
};
TopologyResult lexicographicTopology(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> indegree(n);
    for (const auto& row : g) for (int v : row) ++indegree[v];
    priority_queue<int, vector<int>, greater<int>> ready;
    for (int i = 0; i < n; ++i) if (!indegree[i]) ready.push(i);
    vector<int> order;
    bool unique = true;
    while (!ready.empty()) {
        if (ready.size() != 1) unique = false;
        int u = ready.top(); ready.pop(); order.push_back(u);
        for (int v : g[u]) if (--indegree[v] == 0) ready.push(v);
    }
    bool dag = (int)order.size() == n;
    return {dag, dag && unique, order}; // 有环时 order 只是可处理前缀
}
