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

#include <set>
#include <iterator>

class RemovableMedian {
    multiset<int> lo, hi;
    void rebalance() {
        while (lo.size() > hi.size() + 1) {
            auto it = prev(lo.end());
            hi.insert(*it); lo.erase(it);
        }
        while (lo.size() < hi.size()) {
            auto it = hi.begin();
            lo.insert(*it); hi.erase(it);
        }
    }
public:
    void add(int value) {
        if (lo.empty() || value <= *prev(lo.end())) lo.insert(value);
        else hi.insert(value);
        rebalance();
    }
    void remove(int value) {
        auto it = lo.find(value);
        if (it != lo.end()) lo.erase(it);
        else {
            auto other = hi.find(value);
            if (other == hi.end()) throw invalid_argument("value not present");
            hi.erase(other);
        }
        rebalance();
    }
    double median() const {
        if (lo.empty()) throw out_of_range("no data");
        if (lo.size() != hi.size()) return *prev(lo.end());
        return ((long long)*prev(lo.end()) + *hi.begin()) / 2.0;
    }
};
vector<double> slidingMedians(const vector<int>& a, int k) {
    if (k <= 0 || (size_t)k > a.size()) return {};
    RemovableMedian state;
    vector<double> answer;
    for (size_t i = 0; i < a.size(); ++i) {
        if (i >= (size_t)k) state.remove(a[i - k]);
        state.add(a[i]);
        if (i + 1 >= (size_t)k) answer.push_back(state.median());
    }
    return answer;
}
