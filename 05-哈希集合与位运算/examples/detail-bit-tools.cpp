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

uint32_t bitAt(unsigned k) {
    if (k >= 32) throw out_of_range("bit index must be below 32");
    return uint32_t{1} << k;
}
bool testBit(uint32_t x, unsigned k) { return (x & bitAt(k)) != 0; }
uint32_t setBit(uint32_t x, unsigned k) { return x | bitAt(k); }
uint32_t clearBit(uint32_t x, unsigned k) { return x & ~bitAt(k); }
uint32_t toggleBit(uint32_t x, unsigned k) { return x ^ bitAt(k); }
uint32_t lowBit(uint32_t x) { return x & (uint32_t{0} - x); }
int popcount32(uint32_t x) {
    int count = 0;
    while (x != 0) { x &= x - 1; ++count; }
    return count;
}
