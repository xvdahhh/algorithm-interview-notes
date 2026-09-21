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

vector<vector<int>> chooseK(int n, int k) {
    if (n < 0 || n > 20 || k < 0 || k > n)
        throw invalid_argument("require 0 <= k <= n <= 20");
    vector<vector<int>> answer;
    vector<int> path;
    function<void(int)> dfs = [&](int start) {
        int need = k - (int)path.size();
        if (need == 0) { answer.push_back(path); return; }
        for (int value = start; value <= n - need + 1; ++value) {
            path.push_back(value);
            dfs(value + 1);
            path.pop_back();
        }
    };
    dfs(1);
    return answer;
}
