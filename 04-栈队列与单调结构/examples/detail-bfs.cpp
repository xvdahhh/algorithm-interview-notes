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

vector<int> bfsDistance(const vector<vector<int>>& graph, int source) {
    int n = (int)graph.size();
    if (source < 0 || source >= n) throw out_of_range("invalid source");
    vector<int> distance(n, -1);
    queue<int> pending;
    distance[source] = 0;
    pending.push(source);
    while (!pending.empty()) {
        int u = pending.front(); pending.pop();
        for (int v : graph[u]) {
            if (v < 0 || v >= n) throw out_of_range("invalid neighbor");
            if (distance[v] != -1) continue;
            distance[v] = distance[u] + 1;
            pending.push(v);
        }
    }
    return distance;
}
