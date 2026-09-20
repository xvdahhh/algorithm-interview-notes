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

class MinStack {
    stack<pair<int, int>> st; // {value, minimum so far}
public:
    bool empty() const { return st.empty(); }
    void push(int x) {
        int mn = st.empty() ? x : min(x, st.top().second);
        st.push({x, mn});
    }
    void pop() {
        if (st.empty()) throw out_of_range("empty stack");
        st.pop();
    }
    int top() const {
        if (st.empty()) throw out_of_range("empty stack");
        return st.top().first;
    }
    int getMin() const {
        if (st.empty()) throw out_of_range("empty stack");
        return st.top().second;
    }
};
