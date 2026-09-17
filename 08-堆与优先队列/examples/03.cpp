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

vector<int> mergeSorted(const vector<vector<int>>& a) {
    using Item=tuple<int,int,int>;
    priority_queue<Item,vector<Item>,greater<Item>> pq;
    for (int r=0;r<(int)a.size();++r)
        if (!a[r].empty()) pq.emplace(a[r][0],r,0);
    vector<int> ans;
    while (!pq.empty()) {
        auto [value,r,i]=pq.top(); pq.pop();
        ans.push_back(value);
        if (i+1<(int)a[r].size()) pq.emplace(a[r][i+1],r,i+1);
    }
    return ans;
}
