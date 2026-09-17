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

class SegmentTree {
    int n;
    vector<long long> tree;
public:
    explicit SegmentTree(const vector<int>& a):n((int)a.size()),tree(2*a.size(),0){
        for(int i=0;i<n;++i) tree[n+i]=a[i];
        for(int i=n-1;i>0;--i) tree[i]=tree[i*2]+tree[i*2+1];
    }
    void setValue(int p,long long value){
        if(p<0||p>=n) throw out_of_range("index");
        p+=n; tree[p]=value;
        for(p/=2;p>0;p/=2) tree[p]=tree[p*2]+tree[p*2+1];
    }
    long long query(int l,int r) const {
        if(l<0||r<l||r>n) throw out_of_range("range");
        long long ans=0;
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l&1) ans+=tree[l++];
            if(r&1) ans+=tree[--r];
        }
        return ans;
    }
};
