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

int longestUniqueByWindow(const string& s) {
    array<int, 256> count{}; // 全部初始化为 0
    int left = 0, best = 0;
    for (int right = 0; right < (int)s.size(); ++right) {
        unsigned char c = static_cast<unsigned char>(s[right]);
        ++count[c];
        while (count[c] > 1) {
            unsigned char old = static_cast<unsigned char>(s[left]);
            --count[old];
            ++left;
        }
        best = max(best, right - left + 1);
    }
    return best;
}
