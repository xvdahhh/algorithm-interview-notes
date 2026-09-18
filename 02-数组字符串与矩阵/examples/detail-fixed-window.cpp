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

long long maxFixedWindowSum(const vector<int>& a, int k) {
    if (k <= 0 || k > (int)a.size())
        throw invalid_argument("invalid window length");
    long long sum = 0, best = LLONG_MIN;
    for (int right = 0; right < (int)a.size(); ++right) {
        sum += a[right];
        if (right >= k) sum -= a[right - k];
        if (right >= k - 1) best = max(best, sum);
    }
    return best;
}
