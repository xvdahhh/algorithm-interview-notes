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

uint64_t integerMagnitude(long long x) {
    return x < 0 ? uint64_t(-(x+1))+1 : uint64_t(x);
}
uint64_t gcdMagnitude(long long a, long long b) {
    uint64_t x = integerMagnitude(a), y = integerMagnitude(b);
    while (y) { uint64_t r = x%y; x = y; y = r; }
    return x;
}
optional<uint64_t> lcmMagnitude(long long a, long long b) {
    uint64_t x = integerMagnitude(a), y = integerMagnitude(b);
    if (x == 0 || y == 0) return uint64_t(0);
    uint64_t reduced = x/gcdMagnitude(a,b);
    if (reduced > UINT64_MAX/y) return nullopt;
    return reduced*y;
}
