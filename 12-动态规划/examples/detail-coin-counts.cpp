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

pair<long long,long long> coinCountsMod(vector<int> coins, int amount,
                                         int mod = 1000000007) {
    if (amount < 0 || amount > 200000 || mod < 2 || mod > 1000000007)
        throw invalid_argument("amount/mod");
    for (int c : coins) if (c <= 0) throw invalid_argument("positive coin");
    sort(coins.begin(),coins.end());
    coins.erase(unique(coins.begin(),coins.end()),coins.end());
    vector<long long> combos(amount+1), ordered(amount+1);
    combos[0] = ordered[0] = 1;
    for (int c : coins)
        for (int s = c; s <= amount; ++s)
            combos[s] = (combos[s]+combos[s-c])%mod;
    for (int s = 1; s <= amount; ++s)
        for (int c : coins) {
            if (c > s) break;
            ordered[s] = (ordered[s]+ordered[s-c])%mod;
        }
    return {combos[amount],ordered[amount]};
}
