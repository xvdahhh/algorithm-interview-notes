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

vector<vector<int>> subsets(const vector<int>& a) {
    vector<vector<int>> ans;
    vector<int> path;
    function<void(int)> dfs=[&](int start) {
        ans.push_back(path);
        for (int i=start;i<(int)a.size();++i) {
            path.push_back(a[i]);
            dfs(i+1);
            path.pop_back();
        }
    };
    dfs(0);
    return ans;
}
