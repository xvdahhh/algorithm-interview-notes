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

long long evalRPN(const vector<string>& tokens) {
    vector<long long> st;
    for (const string& t : tokens) {
        bool op = t == "+" || t == "-" || t == "*" || t == "/";
        if (!op) {
            size_t used = 0;
            long long x = stoll(t, &used);
            if (used != t.size()) throw invalid_argument("bad number");
            st.push_back(x);
            continue;
        }
        if (st.size() < 2) throw invalid_argument("missing operand");
        long long rhs = st.back(); st.pop_back();
        long long lhs = st.back(); st.pop_back();
        if (t == "+") st.push_back(lhs + rhs);
        else if (t == "-") st.push_back(lhs - rhs);
        else if (t == "*") st.push_back(lhs * rhs);
        else {
            if (rhs == 0) throw invalid_argument("division by zero");
            if (lhs == LLONG_MIN && rhs == -1)
                throw overflow_error("division overflow");
            st.push_back(lhs / rhs);
        }
    }
    if (st.size() != 1) throw invalid_argument("invalid expression");
    return st.back();
}
