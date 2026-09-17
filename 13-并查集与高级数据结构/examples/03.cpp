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

class Fenwick {
    int n;
    vector<long long> bit;
public:
    explicit Fenwick(int size):n(size),bit(size+1,0){}
    void add(int i,long long delta){
        if(i<1||i>n) throw out_of_range("index");
        for(;i<=n;i+=i&-i) bit[i]+=delta;
    }
    long long prefix(int i) const {
        if(i<0||i>n) throw out_of_range("index");
        long long ans=0;
        for(;i>0;i-=i&-i) ans+=bit[i];
        return ans;
    }
    long long rangeSum(int l,int r) const {
        if(l<1||r>n||l>r) throw out_of_range("range");
        return prefix(r)-prefix(l-1);
    }
};
