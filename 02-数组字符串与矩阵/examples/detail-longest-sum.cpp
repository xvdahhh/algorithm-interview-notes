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

int longestSubarraySum(const vector<int>& a, long long k) {
    unordered_map<long long, int> first;
    first[0] = 0; // 空前缀的位置，以“元素个数”为下标
    long long prefix = 0;
    int best = 0;
    for (int end = 1; end <= (int)a.size(); ++end) {
        prefix += a[end - 1];
        auto it = first.find(prefix - k);
        if (it != first.end()) best = max(best, end - it->second);
        first.emplace(prefix, end); // 已存在时不覆盖，保留最早出现位置
    }
    return best;
}
