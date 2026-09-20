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

pair<uint32_t, uint32_t> twoSingleNumbers(const vector<uint32_t>& a) {
    uint32_t combined = 0;
    for (uint32_t value : a) combined ^= value;
    if (combined == 0) throw invalid_argument("required distinct singles missing");
    uint32_t split = combined & (uint32_t{0} - combined);
    uint32_t first = 0, second = 0;
    for (uint32_t value : a) {
        if ((value & split) == 0) first ^= value;
        else second ^= value;
    }
    return {first, second};
}
