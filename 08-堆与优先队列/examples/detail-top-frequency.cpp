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

struct FrequencyItem { int value; int count; };
struct BetterFrequency {
    bool operator()(const FrequencyItem& a, const FrequencyItem& b) const {
        if (a.count != b.count) return a.count > b.count;
        return a.value < b.value;
    }
};
vector<int> topFrequent(const vector<int>& a, int k) {
    if (k < 0) throw invalid_argument("negative k");
    if (k == 0) return {};
    unordered_map<int, int> count;
    for (int value : a) ++count[value];
    if ((size_t)k > count.size()) throw invalid_argument("k exceeds distinct values");
    priority_queue<FrequencyItem, vector<FrequencyItem>, BetterFrequency> selected;
    for (auto [value, frequency] : count) {
        selected.push({value, frequency});
        if (selected.size() > (size_t)k) selected.pop();
    }
    vector<int> answer;
    while (!selected.empty()) {
        answer.push_back(selected.top().value); selected.pop();
    }
    reverse(answer.begin(), answer.end());
    return answer;
}
