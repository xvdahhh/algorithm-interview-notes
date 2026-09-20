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

vector<int> previousSmaller(const vector<int>& a) {
    vector<int> left(a.size(), -1), st;
    for (int i = 0; i < (int)a.size(); ++i) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        if (!st.empty()) left[i] = st.back();
        st.push_back(i);
    }
    return left;
}
