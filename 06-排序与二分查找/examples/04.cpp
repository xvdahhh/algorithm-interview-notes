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

long long shipCapacity(const vector<int>& w, int days) {
    if (w.empty()) return 0;
    if (days <= 0) throw invalid_argument("days must be positive");
    long long lo = *max_element(w.begin(),w.end());
    long long hi = accumulate(w.begin(),w.end(),0LL);
    auto ok = [&](long long cap) {
        int used=1;
        long long load=0;
        for (int x:w) {
            if (load+x>cap) { ++used; load=0; }
            load+=x;
        }
        return used<=days;
    };
    while (lo<hi) {
        long long mid=lo+(hi-lo)/2;
        if (ok(mid)) hi=mid;
        else lo=mid+1;
    }
    return lo;
}
