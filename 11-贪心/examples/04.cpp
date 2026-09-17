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

long long maxProfitUnlimited(const vector<int>& prices) {
    long long profit=0;
    for(int i=1;i<(int)prices.size();++i)
        profit+=max(0LL,(long long)prices[i]-prices[i-1]);
    return profit;
}
