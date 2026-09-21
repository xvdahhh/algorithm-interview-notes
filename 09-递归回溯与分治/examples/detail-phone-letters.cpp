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

vector<string> phoneLetters(const string& digits) {
    const array<string, 10> letters{"", "", "abc", "def", "ghi", "jkl",
                                  "mno", "pqrs", "tuv", "wxyz"};
    if (digits.size() > 8) throw invalid_argument("output too large");
    for (char c : digits)
        if (c < '2' || c > '9') throw invalid_argument("digits 2..9 required");
    if (digits.empty()) return {};
    vector<string> answer;
    string path;
    function<void(size_t)> dfs = [&](size_t index) {
        if (index == digits.size()) { answer.push_back(path); return; }
        for (char c : letters[digits[index] - '0']) {
            path.push_back(c); dfs(index + 1); path.pop_back();
        }
    };
    dfs(0);
    return answer;
}
