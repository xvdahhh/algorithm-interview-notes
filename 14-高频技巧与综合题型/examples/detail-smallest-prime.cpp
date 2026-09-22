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

class SmallestPrimeTable {
    int limit;
    vector<int> spf, primeList;
public:
    explicit SmallestPrimeTable(int n): limit(n) {
        if (n < 0 || n > 1000000) throw invalid_argument("sieve limit");
        spf.assign(n+1,0);
        for (int i = 2; i <= n; ++i) {
            if (spf[i] == 0) { spf[i] = i; primeList.push_back(i); }
            for (int p : primeList) {
                if (p > spf[i] || 1LL*p*i > n) break;
                spf[p*i] = p;
            }
        }
    }
    const vector<int>& primes() const { return primeList; }
    bool isPrime(int x) const {
        if (x < 0 || x > limit) throw out_of_range("x");
        return x >= 2 && spf[x] == x;
    }
    vector<pair<int,int>> factorize(int x) const {
        if (x < 1 || x > limit) throw out_of_range("1 <= x <= limit");
        vector<pair<int,int>> factors;
        while (x > 1) {
            int p = spf[x], exponent = 0;
            while (x%p == 0) { x /= p; ++exponent; }
            factors.push_back({p,exponent});
        }
        return factors;
    }
};
