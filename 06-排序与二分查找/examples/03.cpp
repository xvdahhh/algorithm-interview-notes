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

pair<int,int> searchRange(const vector<int>& a, int x) {
    auto first = lower_bound(a.begin(), a.end(), x);
    if (first == a.end() || *first != x) return {-1,-1};
    auto after = upper_bound(first, a.end(), x);
    return {(int)(first-a.begin()), (int)(after-a.begin())-1};
}
