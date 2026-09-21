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

vector<vector<int>> frequencyPermutations(vector<int> a) {
    if (a.size() > 9) throw invalid_argument("permutation output too large");
    sort(a.begin(), a.end());
    vector<int> values, count;
    for (int x : a) {
        if (values.empty() || values.back() != x) {
            values.push_back(x); count.push_back(1);
        } else ++count.back();
    }
    vector<vector<int>> answer;
    vector<int> path;
    function<void()> dfs = [&] {
        if (path.size() == a.size()) { answer.push_back(path); return; }
        for (size_t i = 0; i < values.size(); ++i) {
            if (count[i] == 0) continue;
            --count[i]; path.push_back(values[i]);
            dfs();
            path.pop_back(); ++count[i];
        }
    };
    dfs();
    return answer;
}
