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

class UnionFind {
    vector<int> parent,sz;
    int components;
public:
    explicit UnionFind(int n):parent(n),sz(n,1),components(n) {
        iota(parent.begin(),parent.end(),0);
    }
    int find(int x) {
        if(parent[x]!=x) parent[x]=find(parent[x]);
        return parent[x];
    }
    bool unite(int a,int b) {
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        parent[b]=a; sz[a]+=sz[b]; --components;
        return true;
    }
    int count() const { return components; }
};
