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

long long modularPower(long long base, uint64_t exponent, long long mod) {
    if (mod <= 0 || mod > 1000000007LL)
        throw invalid_argument("require 1 <= mod <= 1000000007");
    base %= mod;
    if (base < 0) base += mod;
    long long result = 1 % mod;
    while (exponent != 0) {
        if ((exponent & uint64_t{1}) != 0) result = result * base % mod;
        base = base * base % mod;
        exponent >>= 1;
    }
    return result;
}
