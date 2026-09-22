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

size_t firstAtLeast(const vector<int>& a, int x) {
    size_t l = 0, r = a.size();
    while (l < r) {
        size_t mid = l + (r - l) / 2;
        if (a[mid] < x) l = mid + 1;
        else r = mid;
    }
    return l;
}
size_t firstGreater(const vector<int>& a, int x) {
    size_t l = 0, r = a.size();
    while (l < r) {
        size_t mid = l + (r - l) / 2;
        if (a[mid] <= x) l = mid + 1;
        else r = mid;
    }
    return l;
}
pair<size_t,size_t> equalRange(const vector<int>& a, int x) {
    return {firstAtLeast(a, x), firstGreater(a, x)};
}
