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

int minSubArrayLen(long long target, const vector<int>& a) {
    // 前提：target > 0，所有 a[i] > 0。
    long long sum = 0;
    int left = 0, ans = (int)a.size() + 1;
    for (int right = 0; right < (int)a.size(); ++right) {
        sum += a[right];
        while (sum >= target) {
            ans = min(ans, right - left + 1);
            sum -= a[left++];
        }
    }
    return ans > (int)a.size() ? 0 : ans;
}
