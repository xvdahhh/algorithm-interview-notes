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

long long fastMax(const vector<int>& a) {
    if (a.empty() || a.size() > 100000) throw invalid_argument("size");
    long long ending = a[0], best = a[0];
    for (size_t i = 1; i < a.size(); ++i) {
        ending = max(static_cast<long long>(a[i]), ending + a[i]);
        best = max(best, ending);
    }
    return best;
}
long long slowMax(const vector<int>& a) {
    if (a.empty() || a.size() > 100000) throw invalid_argument("size");
    long long best = LLONG_MIN;
    for (size_t l = 0; l < a.size(); ++l) {
        long long sum = 0;
        for (size_t r = l; r < a.size(); ++r) {
            sum += a[r];
            best = max(best, sum);
        }
    }
    return best;
}
bool checkMax(const vector<int>& a, long long expected) {
    long long actual = fastMax(a);
    if (actual == expected) return true;
    cerr << "input:";
    for (int x : a) cerr << ' ' << x;
    cerr << " expected=" << expected << " actual=" << actual << '\n';
    return false;
}
int main() {
    if (!checkMax({-5,-2,-9}, -2) || !checkMax({0}, 0) ||
        !checkMax({4,-1,2,1}, 6) ||
        !checkMax({INT_MAX,INT_MAX}, 2LL * INT_MAX) ||
        !checkMax({INT_MIN}, INT_MIN)) return 1;
    bool rejected = false;
    try { (void)fastMax({}); } catch (const invalid_argument&) { rejected = true; }
    if (!rejected) { cerr << "empty input accepted\n"; return 1; }
    mt19937 rng(20260922);
    uniform_int_distribution<int> length(1,12), value(-20,20);
    for (int round = 0; round < 2000; ++round) {
        vector<int> a(static_cast<size_t>(length(rng)));
        for (int& x : a) x = value(rng);
        const long long expected = slowMax(a);
        if (!checkMax(a, expected)) return 1;
        reverse(a.begin(), a.end());
        if (!checkMax(a, expected)) return 1;
        for (int& x : a) x *= 2; // small generated values, no int overflow
        if (!checkMax(a, 2 * expected)) return 1;
    }
    cout << "boundary and 2000 differential rounds passed\n";
}
