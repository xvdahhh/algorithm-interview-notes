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

bool containsNearbyDuplicate(const vector<int>& a, int k) {
    if (k <= 0) return false;
    unordered_set<int> window;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i > k) window.erase(a[i - k - 1]);
        if (window.find(a[i]) != window.end()) return true;
        window.insert(a[i]);
    }
    return false;
}
