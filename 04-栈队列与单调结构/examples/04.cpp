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

class TwoStackQueue {
    stack<int> in, out;
    void transfer() {
        if (out.empty()) {
            while (!in.empty()) { out.push(in.top()); in.pop(); }
        }
    }
public:
    void push(int x) { in.push(x); }
    bool empty() const { return in.empty() && out.empty(); }
    int pop() {
        transfer();
        if (out.empty()) throw out_of_range("empty queue");
        int x = out.top(); out.pop(); return x;
    }
    int front() {
        transfer();
        if (out.empty()) throw out_of_range("empty queue");
        return out.top();
    }
};
