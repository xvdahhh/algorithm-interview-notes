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

int longestBoundedWindow(const vector<int>& a, long long limit) {
    if (limit < 0) return 0;
    deque<int> maximum, minimum;
    int left = 0, best = 0;
    for (int right = 0; right < (int)a.size(); ++right) {
        while (!maximum.empty() && a[maximum.back()] <= a[right])
            maximum.pop_back();
        while (!minimum.empty() && a[minimum.back()] >= a[right])
            minimum.pop_back();
        maximum.push_back(right);
        minimum.push_back(right);
        while ((long long)a[maximum.front()] - a[minimum.front()] > limit) {
            if (maximum.front() == left) maximum.pop_front();
            if (minimum.front() == left) minimum.pop_front();
            ++left;
        }
        best = max(best, right - left + 1);
    }
    return best;
}
