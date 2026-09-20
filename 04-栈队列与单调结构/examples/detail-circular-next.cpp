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

vector<int> nextGreaterCircular(const vector<int>& a) {
    int n = (int)a.size();
    vector<int> answer(n, -1), st;
    for (int pass = 0; pass < 2; ++pass) {
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && a[i] > a[st.back()]) {
                answer[st.back()] = a[i];
                st.pop_back();
            }
            if (pass == 0) st.push_back(i);
        }
    }
    return answer;
}
