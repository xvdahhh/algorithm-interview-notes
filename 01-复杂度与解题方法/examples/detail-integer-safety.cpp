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

long long safeProduct(int a, int b) {
    return 1LL * a * b; // 从第一个乘法开始就是 long long
}
long long safeSum(const vector<int>& a) {
    return accumulate(a.begin(), a.end(), 0LL);
}
long long absoluteInt(int x) {
    long long value = x; // 必须先提升，才能安全处理 INT_MIN
    return value < 0 ? -value : value;
}
