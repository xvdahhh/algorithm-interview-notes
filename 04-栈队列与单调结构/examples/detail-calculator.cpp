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

class Calculator {
    string s;
    size_t pos = 0;
    void spaces() { while (pos < s.size() && s[pos] == ' ') ++pos; }
    bool take(char c) {
        spaces();
        if (pos < s.size() && s[pos] == c) { ++pos; return true; }
        return false;
    }
    long long primary() {
        if (take('(')) {
            long long x = expression();
            if (!take(')')) throw invalid_argument("missing )");
            return x;
        }
        spaces();
        if (pos == s.size() || s[pos] < '0' || s[pos] > '9')
            throw invalid_argument("expected number");
        long long x = 0;
        while (pos < s.size() && s[pos] >= '0' && s[pos] <= '9') {
            int digit = s[pos++] - '0';
            if (x > (LLONG_MAX - digit) / 10)
                throw overflow_error("literal overflow");
            x = x * 10 + digit;
        }
        return x;
    }
    long long unary() {
        if (take('+')) return unary();
        if (take('-')) return -unary();
        return primary();
    }
    long long term() {
        long long x = unary();
        for (;;) {
            if (take('*')) x *= unary();
            else if (take('/')) {
                long long y = unary();
                if (y == 0) throw invalid_argument("division by zero");
                if (x == LLONG_MIN && y == -1)
                    throw overflow_error("division overflow");
                x /= y;
            } else return x;
        }
    }
    long long expression() {
        long long x = term();
        for (;;) {
            if (take('+')) x += term();
            else if (take('-')) x -= term();
            else return x;
        }
    }
public:
    long long evaluate(const string& input) {
        s = input; pos = 0;
        long long result = expression();
        spaces();
        if (pos != s.size()) throw invalid_argument("trailing token");
        return result;
    }
};
