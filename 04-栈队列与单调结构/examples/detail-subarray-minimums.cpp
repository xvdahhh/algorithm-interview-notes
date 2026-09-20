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

int sumSubarrayMins(const vector<int>& a) {
    const long long MOD = 1000000007;
    int n = (int)a.size();
    vector<int> left(n), right(n), st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        left[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        right[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        long long contribution = (long long)a[i] * (i - left[i]) % MOD;
        contribution = contribution * (right[i] - i) % MOD;
        result = (result + contribution) % MOD;
    }
    return (int)result;
}
