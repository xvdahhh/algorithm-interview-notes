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

struct CountItem { int key; int id; };
vector<CountItem> stableCountingSort(const vector<CountItem>& a, int keyCount) {
    if (keyCount <= 0 || keyCount > 1000000)
        throw invalid_argument("require 1 <= keyCount <= 1000000");
    vector<size_t> end(keyCount, 0);
    for (const auto& item : a) {
        if (item.key < 0 || item.key >= keyCount)
            throw invalid_argument("key outside [0, keyCount)");
        ++end[item.key];
    }
    for (int key = 1; key < keyCount; ++key) end[key] += end[key - 1];
    vector<CountItem> answer(a.size());
    for (size_t i = a.size(); i > 0; --i) {
        const auto& item = a[i - 1];
        answer[--end[item.key]] = item;
    }
    return answer;
}
