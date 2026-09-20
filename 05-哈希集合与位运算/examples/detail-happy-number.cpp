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

int digitSquareSum(int x) {
    int result = 0;
    while (x > 0) {
        int digit = x % 10;
        result += digit * digit;
        x /= 10;
    }
    return result;
}
bool isHappy(int n) {
    if (n <= 0) return false;
    unordered_set<int> seen;
    while (n != 1) {
        if (!seen.insert(n).second) return false;
        n = digitSquareSum(n);
    }
    return true;
}
