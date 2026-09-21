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

bool wordExists(const vector<string>& board, const string& word) {
    if (board.empty()) return word.empty();
    size_t columns = board[0].size();
    for (const auto& row : board)
        if (row.size() != columns) throw invalid_argument("rectangular board required");
    if (board.size() > 20 || columns > 20)
        throw invalid_argument("board too large for this example");
    if (word.empty()) return true;
    if (columns == 0 || word.size() > board.size()*columns) return false;
    array<int,256> available{}, needed{};
    for (const auto& row : board)
        for (unsigned char c : row) ++available[c];
    for (unsigned char c : word)
        if (++needed[c] > available[c]) return false;
    int rows = (int)board.size(), cols = (int)columns;
    vector<vector<bool>> used(rows, vector<bool>(cols, false));
    const int dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1};
    function<bool(int,int,size_t)> dfs = [&](int r,int c,size_t index) {
        if (used[r][c] || board[r][c] != word[index]) return false;
        if (index + 1 == word.size()) return true;
        used[r][c] = true;
        bool found = false;
        for (int direction=0; direction<4 && !found; ++direction) {
            int nr=r+dr[direction], nc=c+dc[direction];
            if (nr>=0 && nr<rows && nc>=0 && nc<cols)
                found = dfs(nr,nc,index+1);
        }
        used[r][c] = false;
        return found;
    };
    for (int r=0;r<rows;++r)
        for (int c=0;c<cols;++c)
            if (dfs(r,c,0)) return true;
    return false;
}
