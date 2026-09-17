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

// 小规模暴力基线：用于核对最大子数组和优化实现。
long long bruteMaxSubArray(const vector<int>& a){
    if(a.empty()) throw invalid_argument("nonempty required");
    long long best=LLONG_MIN;
    for(int l=0;l<(int)a.size();++l){
        long long sum=0;
        for(int r=l;r<(int)a.size();++r){
            sum+=a[r]; best=max(best,sum);
        }
    }
    return best;
}
