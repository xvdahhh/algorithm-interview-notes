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

int longestConsecutive(const vector<int>& a) {
    unordered_set<long long> values(a.begin(), a.end());
    int ans = 0;
    for (long long x : values) {
        if (values.count(x - 1)) continue;
        long long y = x;
        while (values.count(y)) ++y;
        ans = max(ans, (int)(y - x));
    }
    return ans;
}
