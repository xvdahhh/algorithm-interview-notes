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

int longestSubarrayWithSum(const vector<int>& a, long long k) {
    unordered_map<long long, int> first;
    first.emplace(0, 0); // prefix index, not element index
    long long prefix = 0;
    int best = 0;
    for (int i = 1; i <= (int)a.size(); ++i) {
        prefix += a[i - 1];
        auto it = first.find(prefix - k);
        if (it != first.end()) best = max(best, i - it->second);
        first.emplace(prefix, i); // do not overwrite earlier occurrence
    }
    return best;
}
