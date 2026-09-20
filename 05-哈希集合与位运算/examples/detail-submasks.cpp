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

uint64_t countSubmasks(uint64_t mask) {
    unsigned selected = 0;
    for (uint64_t x = mask; x != 0; x &= x - 1) ++selected;
    if (selected > 20) throw invalid_argument("too many submasks to enumerate");
    uint64_t count = 0;
    uint64_t sub = mask;
    for (;;) {
        // Process this submask here; counting is only a demonstration.
        ++count;
        if (sub == 0) break;
        sub = (sub - 1) & mask;
    }
    return count;
}
