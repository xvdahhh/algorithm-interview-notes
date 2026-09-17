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

struct DSU {
    vector<int> p,sz;
    explicit DSU(int n):p(n),sz(n,1){ iota(p.begin(),p.end(),0); }
    int find(int x){ return p[x]==x ? x : p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b]; return true;
    }
};
optional<long long> kruskal(int n, vector<tuple<int,int,int>> edges) {
    // 每条边为 (权重,u,v)，无向图；节点编号 0..n-1。
    if(n<=1) return 0LL;
    sort(edges.begin(),edges.end());
    DSU dsu(n);
    long long sum=0; int used=0;
    for(auto [w,u,v]:edges)
        if(dsu.unite(u,v)){
            sum+=w;
            if(++used==n-1) return sum;
        }
    return nullopt;
}
