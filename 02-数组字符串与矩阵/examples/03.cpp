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

long long subarraySum(const vector<int>& a, long long k) {
    unordered_map<long long, long long> freq;
    freq[0] = 1;
    long long pre = 0, ans = 0;
    for (int x : a) {
        pre += x;
        auto it = freq.find(pre - k);
        if (it != freq.end()) ans += it->second;
        ++freq[pre];
    }
    return ans;
}
