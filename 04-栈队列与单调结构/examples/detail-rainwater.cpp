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

long long trapRain(const vector<int>& h) {
    vector<int> st;
    long long water = 0;
    for (int i = 0; i < (int)h.size(); ++i) {
        while (!st.empty() && h[i] > h[st.back()]) {
            int bottom = st.back(); st.pop_back();
            if (st.empty()) break;
            int left = st.back();
            long long depth = (long long)min(h[left], h[i]) - h[bottom];
            water += depth * (i - left - 1);
        }
        st.push_back(i);
    }
    return water;
}
