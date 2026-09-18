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

void setZeroes(vector<vector<int>>& a) {
    if (a.empty()) return;
    int rows = (int)a.size(), cols = (int)a[0].size();
    for (const auto& row : a)
        if ((int)row.size() != cols)
            throw invalid_argument("rectangular matrix required");
    if (cols == 0) return;
    bool firstRowZero = false, firstColZero = false;
    for (int col = 0; col < cols; ++col)
        if (a[0][col] == 0) firstRowZero = true;
    for (int r = 0; r < rows; ++r)
        if (a[r][0] == 0) firstColZero = true;
    for (int r = 1; r < rows; ++r)
        for (int col = 1; col < cols; ++col)
            if (a[r][col] == 0) {
                a[r][0] = 0;
                a[0][col] = 0;
            }
    for (int r = 1; r < rows; ++r)
        for (int col = 1; col < cols; ++col)
            if (a[r][0] == 0 || a[0][col] == 0) a[r][col] = 0;
    if (firstRowZero) fill(a[0].begin(), a[0].end(), 0);
    if (firstColZero)
        for (int r = 0; r < rows; ++r) a[r][0] = 0;
}
