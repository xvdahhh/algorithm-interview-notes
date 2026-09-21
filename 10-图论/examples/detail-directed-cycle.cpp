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

vector<int> findDirectedCycle(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> color(n), parent(n, -1);
    for (int s = 0; s < n; ++s) if (!color[s]) {
        vector<pair<int,size_t>> frames;
        color[s] = 1; frames.push_back({s,0});
        while (!frames.empty()) {
            int u = frames.back().first;
            if (frames.back().second == g[u].size()) {
                color[u] = 2; frames.pop_back(); continue;
            }
            int v = g[u][frames.back().second++];
            if (!color[v]) {
                parent[v] = u; color[v] = 1; frames.push_back({v,0});
            } else if (color[v] == 1) {
                vector<int> cycle{u};
                while (cycle.back() != v) cycle.push_back(parent[cycle.back()]);
                reverse(cycle.begin(), cycle.end());
                cycle.push_back(v); return cycle;
            }
        }
    }
    return {};
}
