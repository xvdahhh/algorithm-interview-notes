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

#include "detail-bfs-path.cpp"
#include "detail-multisource-grid.cpp"
#include "detail-undirected-cycle.cpp"
#include "detail-bipartite.cpp"
#include "detail-topo-lex.cpp"
#include "detail-directed-cycle.cpp"
#include "detail-safe-nodes.cpp"
#include "detail-zero-one-bfs.cpp"
#include "detail-minimax-path.cpp"
#include "detail-bellman-ford.cpp"
#include "detail-floyd-marked.cpp"
#include "detail-dag-shortest.cpp"
#include "detail-prim-forest.cpp"
#include "03.cpp"
#include "05.cpp"

bool bruteBipartite(const vector<vector<int>>& g) {
    int n = (int)g.size();
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true;
        for (int u = 0; u < n; ++u) for (int v : g[u])
            if (((mask >> u) & 1) == ((mask >> v) & 1)) ok = false;
        if (ok) return true;
    }
    return false;
}
optional<long long> bruteTree(int n, const vector<tuple<int,int,int>>& edges) {
    if (n <= 1) return 0LL;
    optional<long long> best;
    int m = (int)edges.size(); // 测试仅 n<=5 的简单无向图，m<=10
    for (int mask = 0; mask < (1 << m); ++mask) {
        int count = 0;
        for (int i = 0; i < m; ++i) count += (mask >> i) & 1;
        if (count != n - 1) continue;
        vector<vector<int>> g(n); long long sum = 0;
        for (int i = 0; i < m; ++i) if ((mask >> i) & 1) {
            auto [w,u,v] = edges[i]; sum += w;
            g[u].push_back(v); g[v].push_back(u);
        }
        vector<char> seen(n); queue<int> q; q.push(0); seen[0] = true;
        int reached = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop(); ++reached;
            for (int v : g[u]) if (!seen[v]) { seen[v] = true; q.push(v); }
        }
        if (reached == n && (!best || sum < *best)) best = sum;
    }
    return best;
}
void checkTopology(const vector<vector<int>>& g, const TopologyResult& r) {
    assert(r.dag && r.order.size() == g.size());
    vector<int> pos(g.size(), -1);
    for (int i = 0; i < (int)g.size(); ++i) {
        assert(r.order[i] >= 0 && r.order[i] < (int)g.size());
        assert(pos[r.order[i]] == -1); pos[r.order[i]] = i;
    }
    for (int u = 0; u < (int)g.size(); ++u) for (int v : g[u]) assert(pos[u] < pos[v]);
}
int main() {
    const long long INF = LLONG_MAX / 4;
    vector<vector<int>> diamond{{1,2},{3},{3},{}};
    auto path = shortestUnweightedPath(diamond,0,3);
    assert(path && path->size() == 3 && path->front() == 0 && path->back() == 3);
    for (size_t i = 1; i < path->size(); ++i) {
        const auto& row = diamond[(*path)[i-1]];
        assert(find(row.begin(),row.end(),(*path)[i]) != row.end());
    }
    assert(!shortestUnweightedPath(diamond,3,0));
    assert(shortestUnweightedPath(diamond,2,2) == optional<vector<int>>(vector<int>{2}));
    auto top = lexicographicTopology(diamond); checkTopology(diamond,top);
    assert(!top.unique && top.order == vector<int>({0,1,2,3}));
    assert(lexicographicTopology(vector<vector<int>>{{1},{2},{}}).unique);
    assert(lexicographicTopology({}).dag && lexicographicTopology({}).unique);
    assert(findDirectedCycle(diamond).empty());
    vector<vector<int>> cyclic{{1},{0,2},{}};
    assert(!lexicographicTopology(cyclic).dag);
    auto cycle = findDirectedCycle(cyclic);
    assert(cycle.size() >= 2 && cycle.front() == cycle.back());
    for (size_t i = 1; i < cycle.size(); ++i) {
        const auto& row = cyclic[cycle[i-1]];
        assert(find(row.begin(),row.end(),cycle[i]) != row.end());
    }
    assert(eventualSafeVertices(cyclic) == vector<int>({2}));
    assert(eventualSafeVertices(vector<vector<int>>{{1,2},{},{2}}) == vector<int>({1}));
    assert(!hasUndirectedCycle(3,{{0,1},{1,2}}));
    assert(hasUndirectedCycle(2,{{0,1},{0,1}}));
    assert(hasUndirectedCycle(1,{{0,0}}));
    assert(!hasUndirectedCycle(0,{}));
    vector<vector<int>> grid{{0,1,1},{1,-1,1},{1,1,0}};
    auto saved = grid;
    assert(nearestSources(grid) == vector<vector<int>>({{0,1,2},{1,-1,1},{2,1,0}}));
    assert(grid == saved && nearestSources({}).empty());
    assert(nearestSources({{1,-1}}) == vector<vector<int>>({{-1,-1}}));
    assert(nearestSources({{0,-1,1}}) == vector<vector<int>>({{0,-1,-1}}));
    vector<vector<pair<int,int>>> bottleneck{{{1,5},{2,4}},{{2,1}},{{1,4}}};
    assert(minimumBottleneck(bottleneck,0,1) == optional<long long>(4));
    assert(!minimumBottleneck(bottleneck,2,0));
    assert(minimumBottleneck(bottleneck,0,0) == optional<long long>(0));
    vector<tuple<int,int,int>> negative{{0,1,1},{1,1,-1},{1,2,2},{3,3,-1}};
    auto bf = bellmanFordMarked(4,negative,0);
    assert(!bf.bad[0] && bf.bad[1] && bf.bad[2] && !bf.bad[3] && bf.dist[3] == INF);
    auto fl = allPairsMarked(4,negative);
    assert(fl.bad[0][2] && !fl.bad[0][0] && !fl.bad[0][3] && fl.bad[3][3]);
    assert(allPairsMarked(2,{{0,1,7},{0,1,2}}).dist[0][1] == 2);
    assert(allPairsMarked(4,{{0,3,1},{3,2,1},{2,1,1}}).dist[0][1] == 3);
    assert(!dagDistances(vector<vector<pair<int,int>>>{{{0,0}}},0));
    assert(densePrimForest({}).components == 0);
    assert(densePrimForest({{0}}).cost == 0);
    mt19937 rng(20260921);
    for (int trial = 0; trial < 120; ++trial) {
        int n = 1 + rng() % 5;
        vector<vector<pair<int,int>>> g(n), dag(n);
        vector<vector<int>> plain(n), dagPlain(n);
        vector<tuple<int,int,int>> zeroEdges, signedEdges, dagEdges, mstEdges;
        vector<vector<long long>> matrix(n,vector<long long>(n,INF));
        for (int i = 0; i < n; ++i) matrix[i][i] = 0;
        for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
            if (rng() % 3 == 0) {
                int w = rng() % 2; g[u].push_back({v,w});
                zeroEdges.push_back({u,v,w});
                signedEdges.push_back({u,v,(int)(rng()%7)-3});
            }
            if (u < v && rng() % 2) {
                int w = (int)(rng()%11)-5;
                dag[u].push_back({v,w}); dagPlain[u].push_back(v); dagEdges.push_back({u,v,w});
                plain[u].push_back(v); plain[v].push_back(u);
                matrix[u][v] = matrix[v][u] = w; mstEdges.push_back({w,u,v});
            }
        }
        auto all = allPairsMarked(n,signedEdges);
        for (int s = 0; s < n; ++s) {
            assert(zeroOneDistances(g,s) == dijkstra(g,s));
            assert(zeroOneDistances(g,s) == bellmanFordMarked(n,zeroEdges,s).dist);
            auto b = bellmanFordMarked(n,signedEdges,s);
            for (int t = 0; t < n; ++t) {
                assert(b.bad[t] == all.bad[s][t]);
                if (!b.bad[t]) assert(b.dist[t] == all.dist[s][t]);
            }
            auto d = dagDistances(dag,s);
            assert(d && *d == bellmanFordMarked(n,dagEdges,s).dist);
        }
        checkTopology(dagPlain,lexicographicTopology(dagPlain));
        assert(findDirectedCycle(dagPlain).empty());
        assert(isBipartiteGraph(plain) == bruteBipartite(plain));
        auto p = densePrimForest(matrix); auto k = kruskal(n,mstEdges);
        auto brute = bruteTree(n,mstEdges);
        assert(k == brute && p.edges.size() == (size_t)(n-p.components));
        if (k) assert(p.components == 1 && p.cost == *k);
        else assert(p.components > 1);
        long long sum = 0; vector<pair<int,int>> chosen;
        for (auto [u,v] : p.edges) { assert(matrix[u][v] != INF); sum += matrix[u][v]; chosen.push_back({u,v}); }
        assert(sum == p.cost && !hasUndirectedCycle(n,chosen));
    }
    assert(!isBipartiteGraph(vector<vector<int>>{{0}}));
    assert(!isBipartiteGraph(vector<vector<int>>{{1,2},{0,2},{0,1}}));
    cout << "graph checks passed\n";
}
