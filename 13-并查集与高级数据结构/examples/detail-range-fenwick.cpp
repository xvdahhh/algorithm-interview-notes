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

class RangeAddFenwick {
    int n;
    vector<long long> first, second;
    void addBit(vector<long long>& bit, int p, long long delta) {
        for (int i = p; i <= n; i += i&-i) bit[i] += delta;
    }
    long long sumBit(const vector<long long>& bit, int p) const {
        long long sum = 0;
        for (int i = p; i > 0; i -= i&-i) sum += bit[i];
        return sum;
    }
    void difference(int p, long long delta) {
        if (p > n) return;
        addBit(first,p,delta); addBit(second,p,delta*(p-1));
    }
    void check(int l, int r) const {
        if (l < 0 || r < l || r > n) throw out_of_range("range");
    }
public:
    explicit RangeAddFenwick(int size): n(size) {
        if (n < 0 || n > 1000000) throw invalid_argument("size");
        first.assign(n+1,0); second.assign(n+1,0);
    }
    void add(int l, int r, long long delta) {
        check(l,r); if (l == r) return;
        difference(l+1,delta); difference(r+1,-delta);
    }
    long long prefix(int r) const {
        check(0,r);
        return (long long)r*sumBit(first,r)-sumBit(second,r);
    }
    long long rangeSum(int l, int r) const {
        check(l,r); return prefix(r)-prefix(l);
    }
};
