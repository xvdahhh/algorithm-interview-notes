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

class KthLargestStream {
    size_t k;
    priority_queue<int, vector<int>, greater<int>> selected;
public:
    explicit KthLargestStream(int rank) {
        if (rank <= 0) throw invalid_argument("k must be positive");
        k = (size_t)rank;
    }
    optional<int> add(int value) {
        if (selected.size() < k) selected.push(value);
        else if (value > selected.top()) {
            selected.pop(); selected.push(value);
        }
        if (selected.size() < k) return nullopt;
        return selected.top();
    }
};
