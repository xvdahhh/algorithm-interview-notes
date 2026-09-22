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

optional<pair<size_t,size_t>> twoSumOriginal(const vector<int>& a, long long target) {
    if (target < 2LL * INT_MIN || target > 2LL * INT_MAX) return nullopt;
    unordered_map<long long,size_t> seen;
    for (size_t i = 0; i < a.size(); ++i) {
        const long long need = target - static_cast<long long>(a[i]);
        auto it = seen.find(need);
        if (it != seen.end()) return pair<size_t,size_t>{it->second, i};
        seen.try_emplace(a[i], i);
    }
    return nullopt;
}
