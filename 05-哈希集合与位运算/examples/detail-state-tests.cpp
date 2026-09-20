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

long long countSubarraysWithSum(const vector<int>& a, long long k) {
    unordered_map<long long, long long> frequency;
    frequency[0] = 1;
    long long prefix = 0, answer = 0;
    for (int value : a) {
        prefix += value;
        auto it = frequency.find(prefix - k);
        if (it != frequency.end()) answer += it->second;
        ++frequency[prefix];
    }
    return answer;
}

int longestSubarrayWithSum(const vector<int>& a, long long k) {
    unordered_map<long long, int> first;
    first.emplace(0, 0); // prefix index, not element index
    long long prefix = 0;
    int best = 0;
    for (int i = 1; i <= (int)a.size(); ++i) {
        prefix += a[i - 1];
        auto it = first.find(prefix - k);
        if (it != first.end()) best = max(best, i - it->second);
        first.emplace(prefix, i); // do not overwrite earlier occurrence
    }
    return best;
}

long long countDivisibleSubarrays(const vector<int>& a, int k) {
    if (k <= 0) throw invalid_argument("k must be positive");
    unordered_map<long long, long long> frequency;
    frequency[0] = 1;
    long long remainder = 0, answer = 0;
    for (int value : a) {
        remainder = (remainder + value) % k;
        if (remainder < 0) remainder += k;
        auto it = frequency.find(remainder);
        if (it != frequency.end()) answer += it->second;
        ++frequency[remainder];
    }
    return answer;
}

bool containsNearbyDuplicate(const vector<int>& a, int k) {
    if (k <= 0) return false;
    unordered_set<int> window;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i > k) window.erase(a[i - k - 1]);
        if (window.find(a[i]) != window.end()) return true;
        window.insert(a[i]);
    }
    return false;
}

uint32_t bitAt(unsigned k) {
    if (k >= 32) throw out_of_range("bit index must be below 32");
    return uint32_t{1} << k;
}
bool testBit(uint32_t x, unsigned k) { return (x & bitAt(k)) != 0; }
uint32_t setBit(uint32_t x, unsigned k) { return x | bitAt(k); }
uint32_t clearBit(uint32_t x, unsigned k) { return x & ~bitAt(k); }
uint32_t toggleBit(uint32_t x, unsigned k) { return x ^ bitAt(k); }
uint32_t lowBit(uint32_t x) { return x & (uint32_t{0} - x); }
int popcount32(uint32_t x) {
    int count = 0;
    while (x != 0) { x &= x - 1; ++count; }
    return count;
}

pair<uint32_t, uint32_t> twoSingleNumbers(const vector<uint32_t>& a) {
    uint32_t combined = 0;
    for (uint32_t value : a) combined ^= value;
    if (combined == 0) throw invalid_argument("required distinct singles missing");
    uint32_t split = combined & (uint32_t{0} - combined);
    uint32_t first = 0, second = 0;
    for (uint32_t value : a) {
        if ((value & split) == 0) first ^= value;
        else second ^= value;
    }
    return {first, second};
}

int32_t singleAmongTriples(const vector<int32_t>& a) {
    uint32_t bits = 0;
    for (unsigned bit = 0; bit < 32; ++bit) {
        int remainder = 0;
        for (int32_t value : a) {
            uint32_t u = static_cast<uint32_t>(value);
            remainder = (remainder + int((u >> bit) & uint32_t{1})) % 3;
        }
        if (remainder != 0) bits |= uint32_t{1} << bit;
    }
    int64_t signedValue = bits;
    if ((bits & (uint32_t{1} << 31)) != 0)
        signedValue -= (int64_t{1} << 32);
    return static_cast<int32_t>(signedValue);
}

uint64_t countSubmasks(uint64_t mask) {
    unsigned selected = 0;
    for (uint64_t x = mask; x != 0; x &= x - 1) ++selected;
    if (selected > 20) throw invalid_argument("too many submasks to enumerate");
    uint64_t count = 0;
    uint64_t sub = mask;
    for (;;) {
        // Process this submask here; counting is only a demonstration.
        ++count;
        if (sub == 0) break;
        sub = (sub - 1) & mask;
    }
    return count;
}

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

long long minimumAssignmentCost(const vector<vector<int>>& cost) {
    int n = (int)cost.size();
    if (n > 20) throw invalid_argument("n must not exceed 20");
    for (const auto& row : cost) {
        if ((int)row.size() != n) throw invalid_argument("square matrix required");
        for (int value : row)
            if (value < 0 || value > 1000000000)
                throw invalid_argument("cost outside supported range");
    }
    size_t total = size_t{1} << n;
    const long long INF = LLONG_MAX / 4;
    vector<long long> dp(total, INF);
    dp[0] = 0;
    for (size_t mask = 0; mask < total; ++mask) {
        int person = 0;
        for (size_t bits = mask; bits != 0; bits &= bits - 1) ++person;
        if (person == n || dp[mask] == INF) continue;
        for (int job = 0; job < n; ++job) {
            size_t bit = size_t{1} << job;
            if ((mask & bit) != 0) continue;
            size_t next = mask | bit;
            dp[next] = min(dp[next], dp[mask] + cost[person][job]);
        }
    }
    return dp.back();
}

void require(bool ok, const string& message) {
    if (!ok) throw runtime_error(message);
}
long long bruteCount(const vector<int>& a, long long k) {
    long long result = 0;
    for (int left = 0; left < (int)a.size(); ++left) {
        long long sum = 0;
        for (int right = left; right < (int)a.size(); ++right) {
            sum += a[right];
            if (sum == k) ++result;
        }
    }
    return result;
}
int bruteLongest(const vector<int>& a, long long k) {
    int result = 0;
    for (int left = 0; left < (int)a.size(); ++left) {
        long long sum = 0;
        for (int right = left; right < (int)a.size(); ++right) {
            sum += a[right];
            if (sum == k) result = max(result, right - left + 1);
        }
    }
    return result;
}
long long bruteDivisible(const vector<int>& a, int k) {
    long long result = 0;
    for (int left = 0; left < (int)a.size(); ++left) {
        long long sum = 0;
        for (int right = left; right < (int)a.size(); ++right) {
            sum += a[right];
            if (sum % k == 0) ++result;
        }
    }
    return result;
}
bool bruteNearby(const vector<int>& a, int k) {
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = i + 1; j < (int)a.size(); ++j)
            if (j - i <= k && a[i] == a[j]) return true;
    return false;
}
long long bruteAssignment(const vector<vector<int>>& cost) {
    int n = (int)cost.size();
    vector<int> permutation(n);
    iota(permutation.begin(), permutation.end(), 0);
    long long best = LLONG_MAX;
    do {
        long long value = 0;
        for (int person = 0; person < n; ++person)
            value += cost[person][permutation[person]];
        best = min(best, value);
    } while (next_permutation(permutation.begin(), permutation.end()));
    return best;
}
int main() {
    require(countSubarraysWithSum({0,0,0}, 0) == 6, "empty interval excluded");
    require(longestSubarrayWithSum({1,-1,1,-1}, 0) == 4, "earliest prefix");
    require(countDivisibleSubarrays({-1,5}, 5) == 1, "negative remainder");
    require(containsNearbyDuplicate({1,2,1}, 2), "inclusive distance");
    require(!containsNearbyDuplicate({1,2,1}, 1), "expired element");
    require(lowBit(uint32_t{1} << 31) == (uint32_t{1} << 31), "high lowbit");
    require(popcount32(~uint32_t{0}) == 32, "all bits set");
    require(toggleBit(toggleBit(123, 31), 31) == 123, "toggle involution");
    require(setBit(0, 31) == (uint32_t{1} << 31), "set high bit");
    require(clearBit(~uint32_t{0}, 31) == 0x7fffffffU, "clear high bit");
    bool rejected = false;
    try { (void)bitAt(32); } catch (const out_of_range&) { rejected = true; }
    require(rejected, "invalid shift rejected");
    auto singles = twoSingleNumbers({0, uint32_t{1} << 31, 7, 7});
    require((singles.first == 0 && singles.second == (uint32_t{1} << 31)) ||
            (singles.second == 0 && singles.first == (uint32_t{1} << 31)),
            "two single numbers with high bit");
    require(singleAmongTriples({INT32_MIN,5,5,5}) == INT32_MIN, "signed minimum");
    require(singleAmongTriples({-7,2,2,2}) == -7, "negative single");
    require(countSubmasks(0) == 1 && countSubmasks(10) == 4, "submasks");
    require(modularPower(-2, 5, 13) == 7, "negative modular base");
    require(modularPower(0, 0, 1) == 0, "exponent zero modulo one");
    require(minimumAssignmentCost({{9,2},{3,7}}) == 5, "assignment example");
    mt19937 rng(20260920);
    uniform_int_distribution<int> length(0, 12), value(-5, 5), target(-8, 8);
    for (int run = 0; run < 1000; ++run) {
        vector<int> a(length(rng));
        for (int& x : a) x = value(rng);
        int k = target(rng);
        require(countSubarraysWithSum(a, k) == bruteCount(a, k), "prefix count");
        require(longestSubarrayWithSum(a, k) == bruteLongest(a, k), "longest prefix");
        int divisor = 1 + int(rng() % 7);
        require(countDivisibleSubarrays(a, divisor) == bruteDivisible(a, divisor),
                "divisible prefix");
        int distance = target(rng);
        require(containsNearbyDuplicate(a, distance) == bruteNearby(a, distance),
                "nearby duplicate");
        uint32_t bits = static_cast<uint32_t>(rng());
        int count = 0;
        for (unsigned bit = 0; bit < 32; ++bit) count += int((bits >> bit) & 1U);
        require(popcount32(bits) == count, "popcount");
        uint64_t mask = bits & 255U;
        require(countSubmasks(mask) == (uint64_t{1} << popcount32((uint32_t)mask)),
                "submask count");
        long long base = value(rng), mod = 1 + rng() % 97;
        uint64_t exponent = rng() % 16;
        long long expected = 1 % mod;
        long long normalized = (base % mod + mod) % mod;
        for (uint64_t i = 0; i < exponent; ++i) expected = expected * normalized % mod;
        require(modularPower(base, exponent, mod) == expected, "modular power");
    }
    for (int run = 0; run < 100; ++run) {
        int n = int(rng() % 7);
        vector<vector<int>> cost(n, vector<int>(n));
        for (auto& row : cost)
            for (int& x : row) x = int(rng() % 21);
        require(minimumAssignmentCost(cost) == bruteAssignment(cost), "assignment DP");
    }
    cout << "All chapter 5 checks passed" << endl;
}
