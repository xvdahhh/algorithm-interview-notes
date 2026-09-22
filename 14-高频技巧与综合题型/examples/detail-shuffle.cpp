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

void fisherYatesShuffle(vector<int>& values, mt19937& rng) {
    for (size_t remaining = values.size(); remaining > 1; --remaining) {
        uniform_int_distribution<size_t> choose(0,remaining-1);
        size_t picked = choose(rng);
        swap(values[remaining-1],values[picked]);
    }
}
