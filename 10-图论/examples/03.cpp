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

vector<long long> dijkstra(
    const vector<vector<pair<int,int>>>& g, int source) {
    const long long INF=LLONG_MAX/4;
    if (source<0 || source>=(int)g.size()) throw out_of_range("source");
    vector<long long> dist(g.size(),INF);
    using State=pair<long long,int>;
    priority_queue<State,vector<State>,greater<State>> pq;
    dist[source]=0; pq.push({0,source});
    while (!pq.empty()) {
        auto [d,u]=pq.top(); pq.pop();
        if (d!=dist[u]) continue;
        for (auto [v,w]:g[u]) {
            if (w<0) throw invalid_argument("negative edge");
            if (d+w<dist[v]) {
                dist[v]=d+w;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}
