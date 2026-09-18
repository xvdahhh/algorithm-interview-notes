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

void rotateClockwise(vector<vector<int>>& a) {
    int n = (int)a.size();
    for (const auto& row : a)
        if ((int)row.size() != n)
            throw invalid_argument("square matrix required");
    for (int r = 0; r < n; ++r)
        for (int col = r + 1; col < n; ++col)
            swap(a[r][col], a[col][r]);
    for (auto& row : a) reverse(row.begin(), row.end());
}
