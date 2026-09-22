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

struct BestSubarray { long long sum; int left, right; };
BestSubarray maxSubarrayRange(const vector<int>& a) {
    if (a.empty()) throw invalid_argument("nonempty array required");
    long long ending = a[0];
    int start = 0;
    BestSubarray best{a[0],0,0};
    for (int i = 1; i < (int)a.size(); ++i) {
        if (ending < 0) { ending = a[i]; start = i; }
        else ending += a[i]; // 等于 0 时延续，保留较早左端点
        if (ending > best.sum ||
            (ending == best.sum && (start < best.left ||
             (start == best.left && i < best.right)))) {
            best = {ending,start,i};
        }
    }
    return best;
}
