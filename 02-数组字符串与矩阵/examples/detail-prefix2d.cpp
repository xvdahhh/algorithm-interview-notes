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

class Prefix2D {
    int rows, cols;
    vector<vector<long long>> pre;
public:
    explicit Prefix2D(const vector<vector<int>>& a)
        : rows((int)a.size()), cols(a.empty() ? 0 : (int)a[0].size()),
          pre(rows + 1, vector<long long>(cols + 1, 0)) {
        for (const auto& row : a)
            if ((int)row.size() != cols)
                throw invalid_argument("rectangular matrix required");
        for (int r = 0; r < rows; ++r)
            for (int col = 0; col < cols; ++col)
                pre[r + 1][col + 1] = (long long)a[r][col]
                    + pre[r][col + 1] + pre[r + 1][col] - pre[r][col];
    }
    long long query(int r1, int c1, int r2, int c2) const {
        if (r1 < 0 || c1 < 0 || r2 < r1 || c2 < c1
            || r2 >= rows || c2 >= cols)
            throw out_of_range("invalid rectangle");
        return pre[r2 + 1][c2 + 1] - pre[r1][c2 + 1]
             - pre[r2 + 1][c1] + pre[r1][c1];
    }
};
