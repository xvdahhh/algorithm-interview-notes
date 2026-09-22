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

class CheckedDSU {
    vector<int> parent, size;
    int groups = 0;
    void check(int x) const {
        if (x < 0 || x >= (int)parent.size()) throw out_of_range("vertex");
    }
public:
    explicit CheckedDSU(int n) {
        if (n < 0) throw invalid_argument("n");
        parent.resize(n); size.assign(n,1); groups = n;
        iota(parent.begin(),parent.end(),0);
    }
    int find(int x) {
        check(x);
        int root = x;
        while (parent[root] != root) root = parent[root];
        while (parent[x] != x) {
            int next = parent[x]; parent[x] = root; x = next;
        }
        return root;
    }
    bool unite(int a, int b) {
        check(a); check(b);
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a,b);
        parent[b] = a; size[a] += size[b]; --groups;
        return true;
    }
    bool connected(int a, int b) { check(a); check(b); return find(a) == find(b); }
    int componentSize(int x) { return size[find(x)]; }
    int count() const { return groups; }
};
