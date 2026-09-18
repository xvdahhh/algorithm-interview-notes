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

long long bruteCount(const vector<int>& a, long long k) {
    long long answer = 0;
    for (int left = 0; left < (int)a.size(); ++left) {
        long long sum = 0;
        for (int right = left; right < (int)a.size(); ++right) {
            sum += a[right];
            if (sum == k) ++answer;
        }
    }
    return answer;
}
long long prefixCount(const vector<int>& a, long long k) {
    unordered_map<long long, long long> frequency;
    frequency[0] = 1;
    long long prefix = 0, answer = 0;
    for (int x : a) {
        prefix += x;
        auto it = frequency.find(prefix - k);
        if (it != frequency.end()) answer += it->second;
        ++frequency[prefix];
    }
    return answer;
}
int main() {
    assert(prefixCount({}, 0) == 0);
    assert(prefixCount({0}, 0) == 1);
    assert(prefixCount({0, 0, 0}, 0) == 6);
    assert(prefixCount({1, -1, 1}, 1) == 3);
    assert(prefixCount({1, 1, 1}, 2) == 2);
    assert(prefixCount({1000000000, 1000000000, 1000000000},
                       3000000000LL) == 1);

    mt19937 rng(20260918);
    uniform_int_distribution<int> length(0, 12), value(-3, 3), target(-8, 8);
    for (int trial = 0; trial < 1000; ++trial) {
        vector<int> a(length(rng));
        for (int& x : a) x = value(rng);
        int k = target(rng);
        long long slow = bruteCount(a, k), fast = prefixCount(a, k);
        if (slow != fast) {
            cerr << "Mismatch: k=" << k << ", input:";
            for (int x : a) cerr << ' ' << x;
            cerr << "\nbrute=" << slow << ", prefix=" << fast << '\n';
            return 1;
        }
    }
    cout << "boundary and differential checks passed\n";
}
