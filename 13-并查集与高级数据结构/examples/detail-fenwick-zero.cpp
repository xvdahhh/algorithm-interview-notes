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

class FenwickZero {
    int n;
    vector<long long> bit;
public:
    explicit FenwickZero(const vector<long long>& a): n((int)a.size()) {
        if (a.size() > 1000000) throw invalid_argument("size limit");
        bit.assign(n+1,0);
        for (int i = 1; i <= n; ++i) {
            bit[i] += a[i-1];
            int parent = i+(i&-i);
            if (parent <= n) bit[parent] += bit[i];
        }
    }
    void add(int p, long long delta) {
        if (p < 0 || p >= n) throw out_of_range("index");
        for (int i = p+1; i <= n; i += i&-i) bit[i] += delta;
    }
    long long prefix(int r) const {
        if (r < 0 || r > n) throw out_of_range("prefix");
        long long result = 0;
        for (int i = r; i > 0; i -= i&-i) result += bit[i];
        return result;
    }
    long long rangeSum(int l, int r) const {
        if (l < 0 || r < l || r > n) throw out_of_range("range");
        return prefix(r)-prefix(l);
    }
    void setValue(int p, long long value) {
        if (p < 0 || p >= n) throw out_of_range("index");
        add(p,value-rangeSum(p,p+1));
    }
};
