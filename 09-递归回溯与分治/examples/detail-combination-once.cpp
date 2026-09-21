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

vector<vector<int>> combinationOnce(vector<int> candidates, int target) {
    if (target < 0 || target > 100 || candidates.size() > 20)
        throw invalid_argument("unsupported target or candidate count");
    for (int value : candidates)
        if (value <= 0) throw invalid_argument("positive candidates required");
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> answer;
    vector<int> path;
    function<void(int,int)> dfs = [&](int start, int remaining) {
        if (remaining == 0) { answer.push_back(path); return; }
        for (int i = start; i < (int)candidates.size(); ++i) {
            if (i > start && candidates[i] == candidates[i - 1]) continue;
            if (candidates[i] > remaining) break;
            path.push_back(candidates[i]);
            dfs(i + 1, remaining - candidates[i]);
            path.pop_back();
        }
    };
    dfs(0, target);
    return answer;
}
