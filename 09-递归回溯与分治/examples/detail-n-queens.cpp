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

vector<vector<string>> solveNQueens(int n) {
    if (n < 0 || n > 12) throw invalid_argument("require 0 <= n <= 12");
    if (n == 0) return {{}};
    vector<vector<string>> answer;
    vector<string> board(n, string(n, '.'));
    vector<bool> column(n, false), down(2*n-1, false), up(2*n-1, false);
    function<void(int)> dfs = [&](int row) {
        if (row == n) { answer.push_back(board); return; }
        for (int col = 0; col < n; ++col) {
            int d = row - col + n - 1, u = row + col;
            if (column[col] || down[d] || up[u]) continue;
            board[row][col] = 'Q';
            column[col] = down[d] = up[u] = true;
            dfs(row + 1);
            column[col] = down[d] = up[u] = false;
            board[row][col] = '.';
        }
    };
    dfs(0);
    return answer;
}
