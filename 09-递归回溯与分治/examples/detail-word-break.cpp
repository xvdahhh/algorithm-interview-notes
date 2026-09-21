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

bool wordBreakMemo(const string& text, const vector<string>& dictionary) {
    if (text.size() > 10000) throw invalid_argument("text too large");
    for (const auto& word : dictionary)
        if (word.empty()) throw invalid_argument("empty word forbidden");
    vector<int> memo(text.size() + 1, -1);
    memo[text.size()] = 1;
    function<bool(size_t)> dfs = [&](size_t start) {
        if (memo[start] != -1) return memo[start] != 0;
        for (const string& word : dictionary) {
            if (word.size() <= text.size() - start &&
                text.compare(start, word.size(), word) == 0 &&
                dfs(start + word.size())) {
                memo[start] = 1;
                return true;
            }
        }
        memo[start] = 0;
        return false;
    };
    return dfs(0);
}
