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

long long stockProfitCooldown(const vector<int>& prices) {
    const long long NEG = LLONG_MIN/4;
    long long hold = NEG, sold = NEG, rest = 0;
    for (int price : prices) {
        if (price < 0) throw invalid_argument("price");
        long long oldHold = hold, oldSold = sold, oldRest = rest;
        hold = max(oldHold,oldRest-price);
        sold = oldHold == NEG ? NEG : oldHold+price;
        rest = max(oldRest,oldSold);
    }
    return max(rest,sold);
}
