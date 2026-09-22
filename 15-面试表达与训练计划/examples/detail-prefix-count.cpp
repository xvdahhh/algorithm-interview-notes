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

long long countTargetSubarrays(const vector<int>& a, long long k) {
    if (a.size() > 100000) throw invalid_argument("n exceeds contract");
    const long long n = static_cast<long long>(a.size());
    if (k < n * static_cast<long long>(INT_MIN) ||
        k > n * static_cast<long long>(INT_MAX)) return 0;
    unordered_map<long long,long long> frequency;
    frequency[0] = 1;
    long long prefix = 0, result = 0;
    for (int x : a) {
        prefix += x;
        auto it = frequency.find(prefix - k);
        if (it != frequency.end()) result += it->second;
        ++frequency[prefix];
    }
    return result;
}
