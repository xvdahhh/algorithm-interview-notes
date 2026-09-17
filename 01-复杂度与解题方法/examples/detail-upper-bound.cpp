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

int upperBound(const vector<int>& a, int x) {
    int left = 0, right = (int)a.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (a[mid] > x) right = mid;
        else left = mid + 1;
    }
    return left; // 第一个 >x 的位置；可能为 n
}
