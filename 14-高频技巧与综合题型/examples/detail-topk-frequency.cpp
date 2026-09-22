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

vector<int> topKFrequentStable(const vector<int>& a, int k) {
    if (k < 0) throw invalid_argument("k");
    unordered_map<int,long long> count;
    for (int x : a) ++count[x];
    if ((size_t)k > count.size()) throw invalid_argument("k exceeds distinct count");
    if (!k) return {};
    using Candidate = pair<long long,int>; // 频次、数值
    auto better = [](const Candidate& x, const Candidate& y) {
        if (x.first != y.first) return x.first > y.first;
        return x.second < y.second;
    };
    priority_queue<Candidate,vector<Candidate>,decltype(better)> heap(better);
    for (auto [value,frequency] : count) {
        heap.push({frequency,value});
        if ((int)heap.size() > k) heap.pop();
    }
    vector<Candidate> kept;
    while (!heap.empty()) { kept.push_back(heap.top()); heap.pop(); }
    sort(kept.begin(),kept.end(),better);
    vector<int> answer;
    for (auto [frequency,value] : kept) answer.push_back(value);
    return answer;
}
