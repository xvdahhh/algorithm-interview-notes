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

vector<long long> productExceptSelf(const vector<int>& a) {
    // 前提：下列前缀、后缀及输出乘积均不溢出 long long。
    int n = (int)a.size();
    vector<long long> answer(n, 1);
    long long left = 1;
    for (int i = 0; i < n; ++i) {
        answer[i] = left;
        if (i + 1 < n) left *= a[i];
    }
    long long right = 1;
    for (int i = n - 1; i >= 0; --i) {
        answer[i] *= right;
        if (i > 0) right *= a[i];
    }
    return answer;
}
