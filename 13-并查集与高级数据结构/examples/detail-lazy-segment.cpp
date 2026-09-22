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

class LazyRangeSum {
    struct Node {
        long long sum = 0, setValue = 0, addValue = 0;
        bool hasSet = false;
    };
    int n;
    vector<Node> tree;
    void pull(int p) { tree[p].sum = tree[p*2].sum+tree[p*2+1].sum; }
    void applySet(int p, int len, long long value) {
        tree[p].sum = value*len;
        tree[p].hasSet = true; tree[p].setValue = value; tree[p].addValue = 0;
    }
    void applyAdd(int p, int len, long long delta) {
        tree[p].sum += delta*len;
        if (tree[p].hasSet) tree[p].setValue += delta;
        else tree[p].addValue += delta;
    }
    void push(int p, int l, int r) {
        if (r-l == 1) return;
        int mid = l+(r-l)/2;
        if (tree[p].hasSet) {
            applySet(p*2,mid-l,tree[p].setValue);
            applySet(p*2+1,r-mid,tree[p].setValue);
            tree[p].hasSet = false;
        }
        if (tree[p].addValue != 0) {
            applyAdd(p*2,mid-l,tree[p].addValue);
            applyAdd(p*2+1,r-mid,tree[p].addValue);
            tree[p].addValue = 0;
        }
    }
    void build(int p, int l, int r, const vector<long long>& a) {
        if (r-l == 1) { tree[p].sum = a[l]; return; }
        int mid = l+(r-l)/2;
        build(p*2,l,mid,a); build(p*2+1,mid,r,a); pull(p);
    }
    void update(int p, int l, int r, int ql, int qr, long long x, bool assign) {
        if (ql <= l && r <= qr) {
            if (assign) applySet(p,r-l,x); else applyAdd(p,r-l,x);
            return;
        }
        push(p,l,r); int mid = l+(r-l)/2;
        if (ql < mid) update(p*2,l,mid,ql,qr,x,assign);
        if (qr > mid) update(p*2+1,mid,r,ql,qr,x,assign);
        pull(p);
    }
    long long query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[p].sum;
        push(p,l,r); int mid = l+(r-l)/2; long long answer = 0;
        if (ql < mid) answer += query(p*2,l,mid,ql,qr);
        if (qr > mid) answer += query(p*2+1,mid,r,ql,qr);
        return answer;
    }
    void check(int l, int r) const {
        if (l < 0 || r < l || r > n) throw out_of_range("range");
    }
public:
    explicit LazyRangeSum(const vector<long long>& a): n((int)a.size()) {
        if (a.size() > 1000000) throw invalid_argument("size limit");
        tree.resize(max(1,4*n));
        if (n) build(1,0,n,a);
    }
    void add(int l, int r, long long delta) {
        check(l,r); if (l < r) update(1,0,n,l,r,delta,false);
    }
    void assign(int l, int r, long long value) {
        check(l,r); if (l < r) update(1,0,n,l,r,value,true);
    }
    long long sum(int l, int r) {
        check(l,r); return l == r ? 0 : query(1,0,n,l,r);
    }
};
