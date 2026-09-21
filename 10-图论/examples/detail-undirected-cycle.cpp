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

bool hasUndirectedCycle(int n, const vector<pair<int,int>>& edges) {
    if (n < 0) throw invalid_argument("n");
    vector<vector<pair<int,int>>> g(n);
    for (int id = 0; id < (int)edges.size(); ++id) {
        auto [u,v] = edges[id];
        if (u < 0 || u >= n || v < 0 || v >= n) throw out_of_range("edge");
        g[u].push_back({v,id}); g[v].push_back({u,id});
    }
    vector<char> seen(n, false);
    for (int s = 0; s < n; ++s) if (!seen[s]) {
        stack<pair<int,int>> st;
        seen[s] = true; st.push({s,-1});
        while (!st.empty()) {
            auto [u, incoming] = st.top(); st.pop();
            for (auto [v,id] : g[u]) {
                if (id == incoming) continue;
                if (seen[v]) return true;
                seen[v] = true; st.push({v,id});
            }
        }
    }
    return false;
}
