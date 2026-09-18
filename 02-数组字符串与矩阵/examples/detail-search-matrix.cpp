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

bool searchSortedMatrix(const vector<vector<int>>& a, int target) {
    if (a.empty()) return false;
    int rows = (int)a.size(), cols = (int)a[0].size();
    for (const auto& row : a)
        if ((int)row.size() != cols)
            throw invalid_argument("rectangular matrix required");
    int r = 0, col = cols - 1;
    while (r < rows && col >= 0) {
        if (a[r][col] == target) return true;
        if (a[r][col] > target) --col;
        else ++r;
    }
    return false;
}
