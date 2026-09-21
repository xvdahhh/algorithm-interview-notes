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

long long stockProfitWithFee(const vector<int>& prices, int fee) {
    if (fee < 0) throw invalid_argument("fee");
    const long long NEG = LLONG_MIN/4;
    long long cash = 0, hold = NEG;
    for (int price : prices) {
        if (price < 0) throw invalid_argument("price");
        long long oldCash = cash, oldHold = hold;
        cash = oldCash;
        if (oldHold != NEG) cash = max(cash,oldHold+price-fee);
        hold = max(oldHold,oldCash-price);
    }
    return cash;
}
