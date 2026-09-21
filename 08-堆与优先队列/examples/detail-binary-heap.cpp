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

class IntMinHeap {
    vector<int> data;
    void down(size_t root) {
        size_t n = data.size();
        while (root < n / 2) {
            size_t child = root * 2 + 1;
            if (child + 1 < n && data[child + 1] < data[child]) ++child;
            if (data[root] <= data[child]) break;
            swap(data[root], data[child]);
            root = child;
        }
    }
public:
    explicit IntMinHeap(vector<int> values = {}) : data(move(values)) {
        for (size_t i = data.size() / 2; i > 0; --i) down(i - 1);
    }
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
    int top() const {
        if (empty()) throw out_of_range("empty heap");
        return data[0];
    }
    void push(int value) {
        data.push_back(value);
        size_t i = data.size() - 1;
        while (i > 0) {
            size_t parent = (i - 1) / 2;
            if (data[parent] <= data[i]) break;
            swap(data[parent], data[i]); i = parent;
        }
    }
    int pop() {
        if (empty()) throw out_of_range("empty heap");
        int answer = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!empty()) down(0);
        return answer;
    }
};
