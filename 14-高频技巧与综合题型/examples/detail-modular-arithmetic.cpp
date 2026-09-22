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

uint64_t addReducedMod(uint64_t a, uint64_t b, uint64_t mod) {
    // 内部辅助：mod>0，a<mod，b<mod
    return a >= mod-b ? a-(mod-b) : a+b;
}
uint64_t multiplyMod(uint64_t a, uint64_t b, uint64_t mod) {
    if (mod == 0) throw invalid_argument("mod");
    a %= mod; b %= mod;
    uint64_t answer = 0;
    while (b) {
        if (b&1U) answer = addReducedMod(answer,a,mod);
        b >>= 1;
        a = addReducedMod(a,a,mod);
    }
    return answer;
}
uint64_t powerMod(uint64_t base, uint64_t exponent, uint64_t mod) {
    if (mod == 0) throw invalid_argument("mod");
    uint64_t answer = 1%mod;
    base %= mod;
    while (exponent) {
        if (exponent&1U) answer = multiplyMod(answer,base,mod);
        exponent >>= 1;
        base = multiplyMod(base,base,mod);
    }
    return answer;
}
optional<long long> inverseModSmall(long long a, long long mod) {
    if (mod < 2 || mod > 1000000000) throw invalid_argument("2 <= mod <= 1e9");
    a %= mod; if (a < 0) a += mod;
    long long oldR = mod, r = a, oldT = 0, t = 1;
    while (r) {
        long long q = oldR/r;
        long long nextR = oldR-q*r, nextT = oldT-q*t;
        oldR = r; r = nextR; oldT = t; t = nextT;
    }
    if (oldR != 1) return nullopt;
    oldT %= mod; if (oldT < 0) oldT += mod;
    return oldT;
}
