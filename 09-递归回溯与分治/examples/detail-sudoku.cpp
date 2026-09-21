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

bool solveSudoku(vector<string>& board) {
    if (board.size()!=9) throw invalid_argument("9 rows required");
    for (const auto& line:board)
        if (line.size()!=9) throw invalid_argument("9 columns required");
    array<unsigned,9> row{}, col{}, box{};
    vector<pair<int,int>> empty;
    for (int r=0;r<9;++r) for (int c=0;c<9;++c) {
        if (board[r][c]=='.') { empty.push_back({r,c}); continue; }
        if (board[r][c]<'1' || board[r][c]>'9') throw invalid_argument("bad symbol");
        unsigned bit=1U<<(board[r][c]-'1');
        int b=(r/3)*3+c/3;
        if ((row[r]|col[c]|box[b])&bit) throw invalid_argument("conflicting clues");
        row[r]|=bit; col[c]|=bit; box[b]|=bit;
    }
    auto candidates = [&](int r,int c) {
        return 511U & ~(row[r]|col[c]|box[(r/3)*3+c/3]);
    };
    auto countBits = [](unsigned x) {
        int count=0;
        while (x) { x&=x-1; ++count; }
        return count;
    };
    function<bool(size_t)> dfs = [&](size_t index) {
        if (index==empty.size()) return true;
        size_t best=index;
        int minimum=10;
        for (size_t i=index;i<empty.size();++i) {
            auto [r,c]=empty[i];
            int count=countBits(candidates(r,c));
            if (count<minimum) { minimum=count; best=i; }
        }
        if (minimum==0) return false;
        swap(empty[index],empty[best]);
        auto [r,c]=empty[index];
        int b=(r/3)*3+c/3;
        unsigned options=candidates(r,c);
        for (int digit=0;digit<9;++digit) {
            unsigned bit=1U<<digit;
            if (!(options&bit)) continue;
            row[r]|=bit; col[c]|=bit; box[b]|=bit;
            board[r][c]=char('1'+digit);
            if (dfs(index+1)) return true;
            board[r][c]='.';
            row[r]^=bit; col[c]^=bit; box[b]^=bit;
        }
        swap(empty[index],empty[best]);
        return false;
    };
    return dfs(0);
}
