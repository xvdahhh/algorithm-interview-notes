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

vector<int> dailyTemperatures(const vector<int>& t) {
    vector<int> ans(t.size(), 0), st;
    for (int i = 0; i < (int)t.size(); ++i) {
        while (!st.empty() && t[i] > t[st.back()]) {
            int j = st.back();
            st.pop_back();
            ans[j] = i - j;
        }
        st.push_back(i);
    }
    return ans;
}
