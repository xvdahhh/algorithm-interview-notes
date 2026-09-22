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

class MaxSubarrayTree {
    struct Info {
        bool empty = true;
        long long sum = 0, prefix = 0, suffix = 0, best = 0;
    };
    int n, base = 1;
    vector<Info> tree;
    static Info single(long long x) { return {false,x,x,x,x}; }
    static Info merge(const Info& left, const Info& right) {
        if (left.empty) return right;
        if (right.empty) return left;
        return {false,left.sum+right.sum,
            max(left.prefix,left.sum+right.prefix),
            max(right.suffix,right.sum+left.suffix),
            max({left.best,right.best,left.suffix+right.prefix})};
    }
public:
    explicit MaxSubarrayTree(const vector<int>& a): n((int)a.size()) {
        if (a.size() > 1000000) throw invalid_argument("size limit");
        while (base < n) base *= 2;
        tree.resize(2*base);
        for (int i = 0; i < n; ++i) tree[base+i] = single(a[i]);
        for (int p = base-1; p > 0; --p) tree[p] = merge(tree[p*2],tree[p*2+1]);
    }
    void setValue(int index, int value) {
        if (index < 0 || index >= n) throw out_of_range("index");
        int p = base+index; tree[p] = single(value);
        for (p /= 2; p > 0; p /= 2) tree[p] = merge(tree[p*2],tree[p*2+1]);
    }
    optional<long long> best(int l, int r) const {
        if (l < 0 || r < l || r > n) throw out_of_range("range");
        Info left, right;
        for (l += base,r += base; l < r; l /= 2,r /= 2) {
            if (l&1) left = merge(left,tree[l++]);
            if (r&1) right = merge(tree[--r],right);
        }
        Info result = merge(left,right);
        if (result.empty) return nullopt;
        return result.best;
    }
};
