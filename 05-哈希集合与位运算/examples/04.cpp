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

vector<vector<int>> subsetsByMask(const vector<int>& a) {
    int n = (int)a.size();
    if (n > 20) throw invalid_argument("exponential output too large");
    vector<vector<int>> ans;
    uint64_t total = 1ULL << n;
    for (uint64_t mask = 0; mask < total; ++mask) {
        vector<int> cur;
        for (int i = 0; i < n; ++i)
            if (mask & (1ULL << i)) cur.push_back(a[i]);
        ans.push_back(move(cur));
    }
    return ans;
}
