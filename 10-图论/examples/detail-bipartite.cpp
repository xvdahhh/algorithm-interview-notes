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

bool isBipartiteGraph(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> color(n, -1);
    queue<int> q;
    for (int s = 0; s < n; ++s) if (color[s] == -1) {
        color[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1; q.push(v);
                } else if (color[v] == color[u]) return false;
            }
        }
    }
    return true;
}
