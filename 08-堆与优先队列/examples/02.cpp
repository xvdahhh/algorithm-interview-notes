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

int kthLargest(const vector<int>& a, int k) {
    if (k<=0 || k>(int)a.size()) throw invalid_argument("invalid k");
    priority_queue<int,vector<int>,greater<int>> heap;
    for (int x:a) {
        heap.push(x);
        if ((int)heap.size()>k) heap.pop();
    }
    return heap.top();
}
