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

int32_t singleAmongTriples(const vector<int32_t>& a) {
    uint32_t bits = 0;
    for (unsigned bit = 0; bit < 32; ++bit) {
        int remainder = 0;
        for (int32_t value : a) {
            uint32_t u = static_cast<uint32_t>(value);
            remainder = (remainder + int((u >> bit) & uint32_t{1})) % 3;
        }
        if (remainder != 0) bits |= uint32_t{1} << bit;
    }
    int64_t signedValue = bits;
    if ((bits & (uint32_t{1} << 31)) != 0)
        signedValue -= (int64_t{1} << 32);
    return static_cast<int32_t>(signedValue);
}
