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

int maxNonOverlapping(vector<pair<int,int>> intervals) {
    sort(intervals.begin(),intervals.end(),[](auto a,auto b){
        return a.second<b.second;
    });
    long long end=LLONG_MIN;
    int count=0;
    for(auto [l,r]:intervals){
        if(l>=end){ ++count; end=r; }
    }
    return count;
}
