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

vector<string> generateParenthesis(int n) {
    if (n<0) return {};
    vector<string> ans;
    string path;
    function<void(int,int)> dfs=[&](int left,int right) {
        if (right==n) { ans.push_back(path); return; }
        if (left<n) {
            path.push_back('('); dfs(left+1,right); path.pop_back();
        }
        if (right<left) {
            path.push_back(')'); dfs(left,right+1); path.pop_back();
        }
    };
    dfs(0,0);
    return ans;
}
