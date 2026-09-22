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

#include "detail-two-sum-original.cpp"
#include "detail-unique-pairs.cpp"
#include "detail-search-bounds.cpp"
#include "detail-ranking.cpp"
#include "detail-prefix-count.cpp"
void requireCheck(bool ok, const string& name) {
    if (!ok) throw runtime_error(name);
}
long long slowCount(const vector<int>& a, long long target) {
    long long result = 0;
    for (size_t l = 0; l < a.size(); ++l) {
        long long sum = 0;
        for (size_t r = l; r < a.size(); ++r) {
            sum += a[r];
            if (sum == target) ++result;
        }
    }
    return result;
}
void checkArray(const vector<int>& a, long long target) {
    vector<pair<int,int>> expected;
    for (size_t i = 0; i < a.size(); ++i)
        for (size_t j = i + 1; j < a.size(); ++j)
            if (static_cast<long long>(a[i]) + a[j] == target)
                expected.emplace_back(min(a[i], a[j]), max(a[i], a[j]));
    sort(expected.begin(), expected.end());
    expected.erase(unique(expected.begin(), expected.end()), expected.end());
    auto found = twoSumOriginal(a, target);
    requireCheck(found.has_value() == !expected.empty(), "two-sum existence");
    if (found) {
        auto [i,j] = *found;
        requireCheck(i < a.size() && j < a.size() && i != j, "indices");
        requireCheck(static_cast<long long>(a[i]) + a[j] == target, "sum");
    }
    requireCheck(uniqueValuePairs(a, target) == expected, "unique pairs");
    requireCheck(countTargetSubarrays(a, target) == slowCount(a, target), "prefix count");
    vector<int> ordered = a;
    sort(ordered.begin(), ordered.end());
    for (int x : {INT_MIN, -5, 0, 5, INT_MAX}) {
        auto [l,r] = equalRange(ordered, x);
        requireCheck(l == static_cast<size_t>(lower_bound(ordered.begin(), ordered.end(), x) - ordered.begin()), "lower");
        requireCheck(r == static_cast<size_t>(upper_bound(ordered.begin(), ordered.end(), x) - ordered.begin()), "upper");
    }
}
int main() {
    vector<int> current;
    long long currentTarget = 0;
    try {
        vector<vector<int>> fixed = {{}, {3}, {3,3}, {0,0,0}, {1,-1,1},
            {INT_MIN,INT_MAX}, {INT_MAX,INT_MAX}, {INT_MIN,INT_MIN}};
        vector<long long> targets = {0,1,6,2LL*INT_MAX,2LL*INT_MIN,LLONG_MIN,LLONG_MAX};
        for (const auto& a : fixed) for (long long k : targets) {
            current = a; currentTarget = k; checkArray(a, k);
        }
        requireCheck(countTargetSubarrays(vector<int>(100000,0),0) == 5000050000LL, "64-bit count");
        bool rejected = false;
        try { (void)countTargetSubarrays(vector<int>(100001),0); }
        catch (const invalid_argument&) { rejected = true; }
        requireCheck(rejected, "length contract");
        vector<RankedCandidate> candidates = {{"Bob",90,1},{"Alice",90,2},
            {"Alice",90,0},{"Z",INT_MIN,3},{"A",INT_MAX,4}};
        BetterCandidate comp;
        auto equivalent = [&](const auto& a, const auto& b) { return !comp(a,b) && !comp(b,a); };
        for (const auto& a : candidates) {
            requireCheck(!comp(a,a), "irreflexive");
            for (const auto& b : candidates) for (const auto& c : candidates) {
                requireCheck(!(comp(a,b) && comp(b,a)), "asymmetric");
                if (comp(a,b) && comp(b,c)) requireCheck(comp(a,c), "transitive");
                if (equivalent(a,b) && equivalent(b,c)) requireCheck(equivalent(a,c), "equivalence");
            }
        }
        auto ordered = candidates;
        sort(ordered.begin(), ordered.end(), comp);
        requireCheck(ordered.front().id == 4 && ordered[1].id == 0 && ordered[2].id == 2, "ranking keys");
        for (size_t k = 0; k <= candidates.size()+1; ++k) {
            auto result = bestCandidates(candidates,k);
            requireCheck(result.size() == min(k,candidates.size()), "top-k size");
            for (size_t i = 0; i < result.size(); ++i)
                requireCheck(result[i].id == ordered[i].id, "heap order");
        }
        requireCheck(bestCandidates({},3).empty(), "empty heap");
        mt19937 rng(20260922);
        uniform_int_distribution<int> length(0,10), value(-5,5), target(-15,15);
        for (int round = 0; round < 1000; ++round) {
            current.assign(static_cast<size_t>(length(rng)),0);
            for (int& x : current) x = value(rng);
            currentTarget = target(rng);
            checkArray(current,currentTarget);
        }
        cout << "boundary, comparator and 1000 differential rounds passed\n";
    } catch (const exception& e) {
        cerr << "FAILED: " << e.what() << "; last array case:";
        for (int x : current) cerr << ' ' << x;
        cerr << " target=" << currentTarget << '\n';
        return 1;
    }
}
