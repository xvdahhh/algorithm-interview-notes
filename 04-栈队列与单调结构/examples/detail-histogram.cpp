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

long long largestRectangle(const vector<int>& h) {
    int n = (int)h.size();
    vector<int> st;
    long long best = 0;
    for (int i = 0; i <= n; ++i) {
        int current = i == n ? 0 : h[i];
        while (!st.empty() && h[st.back()] > current) {
            int j = st.back(); st.pop_back();
            int left = st.empty() ? -1 : st.back();
            best = max(best, 1LL * h[j] * (i - left - 1));
        }
        if (i < n) st.push_back(i);
    }
    return best;
}
