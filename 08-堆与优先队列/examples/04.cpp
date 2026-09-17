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

class MedianFinder {
    priority_queue<int> lo;
    priority_queue<int,vector<int>,greater<int>> hi;
public:
    void addNum(int x) {
        if (lo.empty() || x<=lo.top()) lo.push(x);
        else hi.push(x);
        if (lo.size()>hi.size()+1) { hi.push(lo.top()); lo.pop(); }
        if (hi.size()>lo.size()) { lo.push(hi.top()); hi.pop(); }
    }
    double findMedian() const {
        if (lo.empty()) throw out_of_range("no data");
        if (lo.size()!=hi.size()) return lo.top();
        return ((long long)lo.top()+hi.top())/2.0;
    }
};
