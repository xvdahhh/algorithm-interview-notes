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

vector<pair<int, int>> closestPoints(const vector<pair<int, int>>& points, int k) {
    if (k < 0 || (size_t)k > points.size()) throw invalid_argument("invalid k");
    if (k == 0) return {};
    using Entry = pair<long long, size_t>; // squared distance, input index
    priority_queue<Entry> selected;
    for (size_t i = 0; i < points.size(); ++i) {
        auto [x, y] = points[i];
        if (x < -1000000000 || x > 1000000000 ||
            y < -1000000000 || y > 1000000000)
            throw invalid_argument("coordinate outside supported range");
        long long distance = 1LL * x * x + 1LL * y * y;
        selected.push({distance, i});
        if (selected.size() > (size_t)k) selected.pop();
    }
    vector<pair<int, int>> answer;
    while (!selected.empty()) {
        answer.push_back(points[selected.top().second]); selected.pop();
    }
    reverse(answer.begin(), answer.end());
    return answer;
}
