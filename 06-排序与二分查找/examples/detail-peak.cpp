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

int findPeak(const vector<int>& a) {
    if (a.empty()) return -1;
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] < a[mid + 1]) l = mid + 1;
        else r = mid;
    }
    return l;
}
