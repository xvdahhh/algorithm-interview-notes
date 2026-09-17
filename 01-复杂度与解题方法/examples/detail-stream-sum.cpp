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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n) || n < 0) return 0;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        long long x;
        if (!(cin >> x)) return 0;
        sum += x; // 题目需保证总和在 long long 范围内
    }
    cout << sum << '\n';
    return 0;
}
