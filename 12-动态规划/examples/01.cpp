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

long long maxSubArray(const vector<int>& a) {
    if(a.empty()) throw invalid_argument("nonempty array required");
    long long endHere=a[0],best=a[0];
    for(int i=1;i<(int)a.size();++i){
        endHere=max((long long)a[i],endHere+a[i]);
        best=max(best,endHere);
    }
    return best;
}
