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

int minJumps(const vector<int>& a) {
    int n=(int)a.size();
    if(n<=1) return 0;
    long long far=0,end=0;
    int steps=0;
    for(int i=0;i<n-1;++i){
        if(i>far) return -1;
        far=max(far,(long long)i+a[i]);
        if(i==end){
            if(far<=i) return -1;
            ++steps; end=far;
            if(end>=n-1) return steps;
        }
    }
    return -1;
}
