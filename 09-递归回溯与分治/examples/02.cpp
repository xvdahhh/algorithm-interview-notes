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

vector<vector<int>> permuteUnique(vector<int> a) {
    sort(a.begin(),a.end());
    vector<vector<int>> ans;
    vector<int> path;
    vector<bool> used(a.size(),false);
    function<void()> dfs=[&] {
        if (path.size()==a.size()) { ans.push_back(path); return; }
        for (int i=0;i<(int)a.size();++i) {
            if (used[i]) continue;
            if (i>0 && a[i]==a[i-1] && !used[i-1]) continue;
            used[i]=true; path.push_back(a[i]);
            dfs();
            path.pop_back(); used[i]=false;
        }
    };
    dfs();
    return ans;
}
