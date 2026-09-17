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

class PrefixSum {
    vector<long long> pre;
public:
    explicit PrefixSum(const vector<int>& a) : pre(a.size() + 1, 0) {
        for (size_t i = 0; i < a.size(); ++i) pre[i + 1] = pre[i] + a[i];
    }
    long long query(int l, int r) const {
        // pre.size()=n+1；合法 r 满足 r<n。
        if (l < 0 || r < l || (size_t)r >= pre.size() - 1)
            throw out_of_range("invalid closed interval");
        return pre[(size_t)r + 1] - pre[l];
    }
};
int main() {
    PrefixSum p({2, -1, 3, 4});
    assert(p.query(1, 3) == 6);
    assert(p.query(0, 3) == 8);
    assert(p.query(0, 0) == 2);
    assert(p.query(1, 1) == -1);

    PrefixSum large({1000000000, 1000000000, 1000000000});
    assert(large.query(0, 2) == 3000000000LL);

    bool rejected = false;
    try { PrefixSum empty({}); empty.query(0, 0); }
    catch (const out_of_range&) { rejected = true; }
    assert(rejected);
    cout << "prefix tests passed\n";
}
