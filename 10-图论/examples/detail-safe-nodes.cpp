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

vector<int> eventualSafeVertices(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<vector<int>> reverseGraph(n);
    vector<int> remaining(n);
    queue<int> q;
    for (int u = 0; u < n; ++u) {
        remaining[u] = (int)g[u].size();
        if (!remaining[u]) q.push(u);
        for (int v : g[u]) reverseGraph[v].push_back(u);
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : reverseGraph[v]) if (--remaining[u] == 0) q.push(u);
    }
    vector<int> answer;
    for (int i = 0; i < n; ++i) if (!remaining[i]) answer.push_back(i);
    return answer;
}
