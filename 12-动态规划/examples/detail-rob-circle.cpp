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

long long robLinearRange(const vector<int>& value, int left, int right) {
    // 半开区间 [left,right)，调用者保证下标合法
    long long prev2 = 0, prev1 = 0;
    for (int i = left; i < right; ++i) {
        long long current = max(prev1,prev2+value[i]);
        prev2 = prev1; prev1 = current;
    }
    return prev1;
}
long long robCircle(const vector<int>& value) {
    int n = (int)value.size();
    if (!n) return 0;
    if (n == 1) return max(0LL,(long long)value[0]);
    return max(robLinearRange(value,0,n-1),robLinearRange(value,1,n));
}
