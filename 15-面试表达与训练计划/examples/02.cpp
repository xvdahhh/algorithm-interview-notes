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

long long kadane(const vector<int>& a){
    if(a.empty()) throw invalid_argument("nonempty required");
    long long cur=a[0],ans=a[0];
    for(int i=1;i<(int)a.size();++i){
        cur=max((long long)a[i],cur+a[i]); ans=max(ans,cur);
    }
    return ans;
}
int main(){
    assert(kadane({-5,-2,-9})==-2);
    assert(kadane({0})==0);
    assert(kadane({4,-1,2,1})==6);
    assert(kadane({-2,1,-3,4,-1,2,1,-5,4})==6);
    cout<<"all checks passed\n";
}
