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

vector<int> spiralOrder(const vector<vector<int>>& a) {
    if (a.empty() || a[0].empty()) return {};
    vector<int> ans;
    int top = 0, bottom = (int)a.size()-1;
    int left = 0, right = (int)a[0].size()-1;
    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; ++c) ans.push_back(a[top][c]);
        ++top;
        for (int r = top; r <= bottom; ++r) ans.push_back(a[r][right]);
        --right;
        if (top <= bottom) {
            for (int c = right; c >= left; --c) ans.push_back(a[bottom][c]);
            --bottom;
        }
        if (left <= right) {
            for (int r = bottom; r >= top; --r) ans.push_back(a[r][left]);
            ++left;
        }
    }
    return ans;
}
