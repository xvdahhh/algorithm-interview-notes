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

vector<int> maxSlidingWindow(const vector<int>& a, int k) {
    if (k <= 0 || k > (int)a.size()) return {};
    deque<int> q;
    vector<int> ans;
    for (int i = 0; i < (int)a.size(); ++i) {
        while (!q.empty() && q.front() <= i-k) q.pop_front();
        while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k-1) ans.push_back(a[q.front()]);
    }
    return ans;
}
