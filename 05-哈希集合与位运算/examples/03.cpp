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

int singleNumber(const vector<int>& a) {
    int ans = 0;
    for (int x : a) ans ^= x;
    return ans;
}
int countBits(uint32_t x) {
    int count = 0;
    while (x) {
        x &= x - 1;
        ++count;
    }
    return count;
}
bool isPowerOfTwo(uint32_t x) {
    return x != 0 && (x & (x - 1)) == 0;
}
