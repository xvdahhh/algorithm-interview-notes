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

vector<vector<int>> uniqueSubsets(vector<int> a) {
    if (a.size() > 20) throw invalid_argument("too many elements");
    sort(a.begin(), a.end());
    vector<vector<int>> answer;
    vector<int> path;
    function<void(int)> dfs = [&](int start) {
        answer.push_back(path);
        for (int i = start; i < (int)a.size(); ++i) {
            if (i > start && a[i] == a[i - 1]) continue;
            path.push_back(a[i]); dfs(i + 1); path.pop_back();
        }
    };
    dfs(0);
    return answer;
}
