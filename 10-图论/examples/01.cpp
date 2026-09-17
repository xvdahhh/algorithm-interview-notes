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

vector<int> bfsDistances(const vector<vector<int>>& g, int source) {
    int n=(int)g.size();
    if (source<0 || source>=n) throw out_of_range("source");
    vector<int> dist(n,-1);
    queue<int> q;
    dist[source]=0; q.push(source);
    while (!q.empty()) {
        int u=q.front(); q.pop();
        for (int v:g[u]) {
            if (dist[v]!=-1) continue;
            dist[v]=dist[u]+1;
            q.push(v);
        }
    }
    return dist;
}
