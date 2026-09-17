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

pair<int,int> twoSumSorted(const vector<int>& a,long long target){
    int l=0,r=(int)a.size()-1;
    while(l<r){
        long long sum=(long long)a[l]+a[r];
        if(sum==target) return {l,r};
        if(sum<target) ++l;
        else --r;
    }
    return {-1,-1};
}
