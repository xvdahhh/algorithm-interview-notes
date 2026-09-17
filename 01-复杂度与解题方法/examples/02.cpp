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

long long modPow(long long a, long long e, long long mod) {
    // 前提：e >= 0，1 <= mod <= 1e9，保证乘法不溢出。
    long long ans = 1 % mod;
    a = (a % mod + mod) % mod;
    while (e > 0) {
        if (e & 1LL) ans = ans * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return ans;
}
