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

int longestUnique(const string& s) {
    array<int, 256> last;
    last.fill(-1);
    int left = 0, ans = 0;
    for (int right = 0; right < (int)s.size(); ++right) {
        unsigned char c = s[right];
        left = max(left, last[c] + 1);
        last[c] = right;
        ans = max(ans, right - left + 1);
    }
    return ans;
}
