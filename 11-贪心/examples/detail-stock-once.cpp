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

long long stockProfitOnce(const vector<int>& prices) {
    long long lowest = LLONG_MAX, answer = 0;
    for (int price : prices) {
        if (price < 0) throw invalid_argument("price");
        if (lowest != LLONG_MAX) answer = max(answer,(long long)price-lowest);
        lowest = min(lowest,(long long)price);
    }
    return answer;
}
