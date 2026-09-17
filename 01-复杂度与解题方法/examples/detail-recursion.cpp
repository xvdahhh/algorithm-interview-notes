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

long long sumRecursive(int n) {
    // 前提：0 <= n <= 1000000；实际递归深度仍可能超过系统栈限制。
    if (n == 0) return 0;
    return n + sumRecursive(n - 1);
}
long long sumIterative(int n) {
    long long total = 0;
    for (int i = 1; i <= n; ++i) total += i;
    return total;
}
