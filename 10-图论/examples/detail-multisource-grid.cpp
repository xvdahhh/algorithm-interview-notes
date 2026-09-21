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

vector<vector<int>> nearestSources(const vector<vector<int>>& grid) {
    int r = (int)grid.size();
    if (!r) return {};
    int c = (int)grid[0].size();
    for (const auto& row : grid) {
        if ((int)row.size() != c) throw invalid_argument("ragged grid");
        for (int x : row) if (x < -1 || x > 1)
            throw invalid_argument("cell");
    }
    vector<vector<int>> d(r, vector<int>(c, -1));
    queue<pair<int,int>> q;
    for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j)
        if (grid[i][j] == 0) { d[i][j] = 0; q.push({i,j}); }
    const int di[] = {-1,1,0,0}, dj[] = {0,0,-1,1};
    while (!q.empty()) {
        auto [i,j] = q.front(); q.pop();
        for (int k = 0; k < 4; ++k) {
            int x = i + di[k], y = j + dj[k];
            if (x < 0 || x >= r || y < 0 || y >= c) continue;
            if (grid[x][y] == -1 || d[x][y] != -1) continue;
            d[x][y] = d[i][j] + 1; q.push({x,y});
        }
    }
    return d;
}
