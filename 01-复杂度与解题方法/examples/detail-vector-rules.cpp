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

vector<int> makeSquares(int n) {
    // 前提：0 <= n <= 46341，保证 i*i 可以放入常见 32 位 int。
    vector<int> result;
    result.reserve(n); // 只预留容量，size 仍为 0
    for (int i = 0; i < n; ++i) result.push_back(i * i);
    return result;
}
void setAllZero(vector<int>& a) {
    for (auto& x : a) x = 0; // 去掉 & 只会修改每次循环的副本
}
void printBackward(const vector<int>& a) {
    // 前提：元素数可放入 int；先转成带符号数，再减 1。
    for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i)
        cout << a[i] << ' ';
    cout << '\n';
}
