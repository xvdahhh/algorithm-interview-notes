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

class RollbackDSU {
    struct Change { int child, root, oldSize; };
    vector<int> parent, size;
    vector<Change> history;
    int groups = 0;
    void check(int x) const {
        if (x < 0 || x >= (int)parent.size()) throw out_of_range("vertex");
    }
public:
    explicit RollbackDSU(int n) {
        if (n < 0) throw invalid_argument("n");
        parent.resize(n); size.assign(n,1); groups = n;
        iota(parent.begin(),parent.end(),0);
    }
    int find(int x) const {
        check(x);
        while (x != parent[x]) x = parent[x];
        return x;
    }
    size_t snapshot() const { return history.size(); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a,b);
        history.push_back({b,a,size[a]});
        parent[b] = a; size[a] += size[b]; --groups;
        return true;
    }
    void rollback(size_t snap) {
        if (snap > history.size()) throw out_of_range("snapshot");
        while (history.size() > snap) {
            auto change = history.back(); history.pop_back();
            parent[change.child] = change.child;
            size[change.root] = change.oldSize; ++groups;
        }
    }
    int count() const { return groups; }
    int componentSize(int x) const { return size[find(x)]; }
};
