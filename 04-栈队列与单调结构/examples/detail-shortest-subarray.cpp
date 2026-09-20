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

int shortestSubarray(const vector<int>& a, long long k) {
    int n = (int)a.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + a[i];
    deque<int> candidates;
    int best = INT_MAX;
    for (int i = 0; i <= n; ++i) {
        while (!candidates.empty() &&
               prefix[i] - prefix[candidates.front()] >= k) {
            best = min(best, i - candidates.front());
            candidates.pop_front();
        }
        while (!candidates.empty() &&
               prefix[candidates.back()] >= prefix[i])
            candidates.pop_back();
        candidates.push_back(i);
    }
    return best == INT_MAX ? -1 : best;
}
