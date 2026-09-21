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

vector<long long> expressionResults(const string& expression) {
    vector<int> numbers;
    vector<char> operators;
    size_t pos = 0;
    while (pos < expression.size()) {
        if (expression[pos] < '0' || expression[pos] > '9')
            throw invalid_argument("expected nonnegative integer");
        int value = 0;
        while (pos < expression.size() && expression[pos] >= '0' && expression[pos] <= '9') {
            int digit = expression[pos++] - '0';
            if (value > (100 - digit) / 10) throw invalid_argument("number exceeds 100");
            value = value * 10 + digit;
        }
        numbers.push_back(value);
        if (numbers.size() > 8) throw invalid_argument("too many operands");
        if (pos == expression.size()) break;
        char op = expression[pos++];
        if (op != '+' && op != '-' && op != '*') throw invalid_argument("bad operator");
        operators.push_back(op);
        if (pos == expression.size()) throw invalid_argument("missing operand");
    }
    if (numbers.empty()) throw invalid_argument("empty expression");
    int n = (int)numbers.size();
    vector<vector<vector<long long>>> memo(n, vector<vector<long long>>(n));
    vector<vector<bool>> ready(n, vector<bool>(n, false));
    function<const vector<long long>&(int,int)> solve =
        [&](int left, int right) -> const vector<long long>& {
            if (ready[left][right]) return memo[left][right];
            auto& result = memo[left][right];
            if (left == right) result.push_back(numbers[left]);
            else for (int split = left; split < right; ++split) {
                const auto& a = solve(left, split);
                const auto& b = solve(split + 1, right);
                for (long long x : a) for (long long y : b) {
                    char op = operators[split];
                    if (op == '+') result.push_back(x + y);
                    else if (op == '-') result.push_back(x - y);
                    else result.push_back(x * y);
                }
            }
            ready[left][right] = true;
            return result;
        };
    return solve(0, n - 1);
}
