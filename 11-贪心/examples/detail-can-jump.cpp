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

bool canReachEnd(const vector<int>& a) {
    for (int x : a) if (x < 0) throw invalid_argument("jump");
    if (a.empty()) return false;
    int n = (int)a.size();
    long long far = 0;
    for (int i = 0; i < n; ++i) {
        if (i > far) return false;
        far = max(far,min((long long)n-1,(long long)i+a[i]));
        if (far == n-1) return true;
    }
    return false;
}
