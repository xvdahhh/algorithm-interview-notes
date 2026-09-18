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

vector<long long> applyRangeAdds(
    const vector<int>& a,
    const vector<tuple<int, int, long long>>& updates) {
    int n = (int)a.size();
    vector<long long> diff(n + 1, 0);
    for (int i = 0; i < n; ++i)
        diff[i] = (long long)a[i] - (i == 0 ? 0LL : a[i - 1]);
    for (auto [left, right, value] : updates) {
        if (left < 0 || right < left || right >= n)
            throw out_of_range("invalid update interval");
        diff[left] += value;
        diff[right + 1] -= value; // right=n-1 时写入 diff[n] 仍安全
    }
    vector<long long> result(n);
    long long current = 0;
    for (int i = 0; i < n; ++i) {
        current += diff[i];
        result[i] = current;
    }
    return result;
}
