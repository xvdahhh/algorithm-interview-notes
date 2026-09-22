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

bool equalPartition(const vector<int>& a) {
    long long sum = 0;
    for (int x : a) {
        if (x < 0) throw invalid_argument("nonnegative values");
        sum += x;
    }
    if (sum % 2) return false;
    if (sum/2 > 200000) throw invalid_argument("teaching target limit");
    int target = (int)(sum/2);
    vector<char> reachable(target+1,false); reachable[0] = true;
    for (int x : a)
        for (int c = target; c >= x; --c)
            if (reachable[c-x]) reachable[c] = true;
    return reachable[target];
}
