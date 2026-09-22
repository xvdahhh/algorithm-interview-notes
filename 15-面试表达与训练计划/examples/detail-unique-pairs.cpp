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

vector<pair<int,int>> uniqueValuePairs(vector<int> a, long long target) {
    vector<pair<int,int>> result;
    if (a.size() < 2) return result;
    sort(a.begin(), a.end());
    size_t l = 0, r = a.size() - 1;
    while (l < r) {
        long long sum = static_cast<long long>(a[l]) + a[r];
        if (sum < target) ++l;
        else if (sum > target) --r;
        else {
            const int left = a[l], right = a[r];
            result.emplace_back(left, right);
            while (l < r && a[l] == left) ++l;
            while (l < r && a[r] == right) --r;
        }
    }
    return result;
}
