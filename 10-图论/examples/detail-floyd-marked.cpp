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

struct FloydResult {
    vector<vector<long long>> dist;
    vector<vector<char>> bad;
};
FloydResult allPairsMarked(int n, const vector<tuple<int,int,int>>& edges) {
    if (n < 0 || n > 1000000) throw invalid_argument("n");
    for (auto [u,v,w] : edges) {
        if (u < 0 || u >= n || v < 0 || v >= n) throw out_of_range("edge");
        if (w < -1000000000 || w > 1000000000) throw invalid_argument("weight");
    }
    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> d(n, vector<long long>(n, INF));
    for (int i = 0; i < n; ++i) d[i][i] = 0;
    for (auto [u,v,w] : edges) d[u][v] = min(d[u][v], (long long)w);
    for (int k = 0; k < n; ++k) {
        auto old = d;
        for (int i = 0; i < n; ++i) if (old[i][k] != INF)
            for (int j = 0; j < n; ++j) if (old[k][j] != INF) {
                long long candidate = max(-INF, old[i][k] + old[k][j]);
                d[i][j] = min(old[i][j], candidate);
            }
    }
    vector<vector<char>> bad(n, vector<char>(n, false));
    for (int k = 0; k < n; ++k) if (d[k][k] < 0)
        for (int i = 0; i < n; ++i) if (d[i][k] != INF)
            for (int j = 0; j < n; ++j) if (d[k][j] != INF) bad[i][j] = true;
    return {d,bad};
}
