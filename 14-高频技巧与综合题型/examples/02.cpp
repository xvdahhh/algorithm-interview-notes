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

int minMeetingRooms(const vector<pair<int,int>>& meetings){
    vector<pair<int,int>> events;
    for(auto [l,r]:meetings){
        if(l>r) throw invalid_argument("invalid interval");
        if(l==r) continue;
        events.push_back({l,1});
        events.push_back({r,-1});
    }
    sort(events.begin(),events.end());
    int active=0,best=0;
    for(auto [time,delta]:events){
        active+=delta;
        best=max(best,active);
    }
    return best;
}
