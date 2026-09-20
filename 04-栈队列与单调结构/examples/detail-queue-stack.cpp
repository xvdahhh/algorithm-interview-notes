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

class QueueStack {
    queue<int> q;
public:
    bool empty() const { return q.empty(); }
    void push(int x) {
        size_t oldSize = q.size();
        q.push(x);
        for (size_t i = 0; i < oldSize; ++i) {
            int front = q.front(); q.pop();
            q.push(front);
        }
    }
    int pop() {
        if (q.empty()) throw out_of_range("empty stack");
        int value = q.front(); q.pop();
        return value;
    }
    int top() const {
        if (q.empty()) throw out_of_range("empty stack");
        return q.front();
    }
};
