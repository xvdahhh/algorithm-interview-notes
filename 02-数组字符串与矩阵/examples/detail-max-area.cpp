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

long long maxArea(const vector<int>& height) {
    // 前提：所有高度非负。
    int left = 0, right = (int)height.size() - 1;
    long long best = 0;
    while (left < right) {
        best = max(best, 1LL * (right - left)
                         * min(height[left], height[right]));
        if (height[left] <= height[right]) ++left;
        else --right;
    }
    return best;
}
