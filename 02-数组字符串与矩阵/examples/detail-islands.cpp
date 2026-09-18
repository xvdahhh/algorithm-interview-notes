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

int countIslands(vector<vector<char>>& grid) {
    if (grid.empty()) return 0;
    int rows = (int)grid.size(), cols = (int)grid[0].size();
    for (const auto& row : grid)
        if ((int)row.size() != cols)
            throw invalid_argument("rectangular grid required");
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    int count = 0;
    for (int r = 0; r < rows; ++r)
        for (int col = 0; col < cols; ++col) {
            if (grid[r][col] != '1') continue;
            ++count;
            queue<pair<int, int>> pending;
            grid[r][col] = '0'; // 入队时即标记
            pending.push({r, col});
            while (!pending.empty()) {
                auto [x, y] = pending.front();
                pending.pop();
                for (int dir = 0; dir < 4; ++dir) {
                    int nx = x + dr[dir], ny = y + dc[dir];
                    if (nx < 0 || nx >= rows || ny < 0 || ny >= cols)
                        continue;
                    if (grid[nx][ny] != '1') continue;
                    grid[nx][ny] = '0';
                    pending.push({nx, ny});
                }
            }
        }
    return count;
}
