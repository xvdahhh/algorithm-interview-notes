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

#include "detail-interval-selection.cpp"
#include "detail-min-arrows.cpp"
#include "detail-interval-cover.cpp"
#include "detail-assign-resources.cpp"
#include "detail-can-jump.cpp"
#include "detail-jump-path.cpp"
#include "detail-partition-labels.cpp"
#include "detail-gas-station.cpp"
#include "detail-merge-checked.cpp"
#include "detail-adjacent-merge.cpp"
#include "detail-stock-once.cpp"
#include "detail-stock-fee.cpp"
#include "detail-stock-cooldown.cpp"
#include "02.cpp"
#include "03.cpp"
#include "04.cpp"

int bitCount(int mask) {
    int count = 0;
    while (mask) { count += mask & 1; mask >>= 1; }
    return count;
}
int bruteSchedule(const vector<pair<int,int>>& a) {
    int n = (int)a.size(), best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true;
        for (int i = 0; i < n; ++i) if ((mask >> i) & 1)
            for (int j = i+1; j < n; ++j) if ((mask >> j) & 1)
                if (max(a[i].first,a[j].first) < min(a[i].second,a[j].second)) ok = false;
        if (ok) best = max(best,bitCount(mask));
    }
    return best;
}
int bruteArrows(const vector<pair<int,int>>& a) {
    vector<int> endpoints;
    for (auto [l,r] : a) { endpoints.push_back(l); endpoints.push_back(r); }
    sort(endpoints.begin(),endpoints.end());
    endpoints.erase(unique(endpoints.begin(),endpoints.end()),endpoints.end());
    int best = (int)a.size();
    // 闭区间的最优刺点总可移动到一个端点；仅用于很小输入。
    for (int mask = 0; mask < (1 << endpoints.size()); ++mask) {
        if (bitCount(mask) >= best) continue;
        bool ok = true;
        for (auto [l,r] : a) {
            bool hit = false;
            for (int j = 0; j < (int)endpoints.size(); ++j)
                if (((mask >> j) & 1) && l <= endpoints[j] && endpoints[j] <= r) hit = true;
            if (!hit) ok = false;
        }
        if (ok) best = bitCount(mask);
    }
    return best;
}
optional<int> bruteCover(vector<pair<int,int>> a, int left, int right) {
    if (left == right) return 0;
    sort(a.begin(),a.end());
    optional<int> best; int n = (int)a.size();
    for (int mask = 0; mask < (1 << n); ++mask) {
        int reach = left;
        for (int i = 0; i < n; ++i) if ((mask >> i) & 1) {
            if (a[i].first > reach) break;
            reach = max(reach,a[i].second);
        }
        if (reach >= right && (!best || bitCount(mask) < *best)) best = bitCount(mask);
    }
    return best;
}
int bruteResources(const vector<int>& needs, const vector<int>& sizes) {
    function<int(int,int)> dfs = [&](int i,int mask) {
        if (i == (int)needs.size()) return 0;
        int best = dfs(i+1,mask);
        for (int j = 0; j < (int)sizes.size(); ++j)
            if (!((mask >> j) & 1) && sizes[j] >= needs[i])
                best = max(best,1+dfs(i+1,mask|(1 << j)));
        return best;
    };
    return dfs(0,0);
}
int bruteJumps(const vector<int>& a) {
    if (a.empty()) return -1;
    int n = (int)a.size();
    vector<int> d(n,-1); queue<int> q; d[0] = 0; q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = u+1; v < n && (long long)v <= (long long)u+a[u]; ++v)
            if (d[v] == -1) { d[v] = d[u]+1; q.push(v); }
    }
    return d[n-1];
}
int brutePartitions(const string& s) {
    if (s.empty()) return 0;
    int n = (int)s.size(), best = 0;
    for (int cuts = 0; cuts < (1 << (n-1)); ++cuts) {
        array<int,256> owner; owner.fill(-1);
        int part = 0; bool ok = true;
        for (int i = 0; i < n; ++i) {
            unsigned char c = (unsigned char)s[i];
            if (owner[c] != -1 && owner[c] != part) ok = false;
            owner[c] = part;
            if (i < n-1 && ((cuts >> i) & 1)) ++part;
        }
        if (ok) best = max(best,part+1);
    }
    return best;
}
bool validGasStart(const vector<int>& gas, const vector<int>& cost, int start) {
    int n = (int)gas.size();
    if (start < 0 || start >= n) return false;
    long long tank = 0;
    for (int step = 0; step < n; ++step) {
        int i = (start+step)%n; tank += (long long)gas[i]-cost[i];
        if (tank < 0) return false;
    }
    return true;
}
long long bruteMerge(vector<long long> a, bool adjacent) {
    if (a.size() <= 1) return 0;
    long long best = LLONG_MAX;
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = i+1; j < (int)a.size(); ++j) {
            if (adjacent && j != i+1) continue;
            auto next = a;
            long long merged = a[i]+a[j];
            next[i] = merged; next.erase(next.begin()+j);
            best = min(best,merged+bruteMerge(next,adjacent));
        }
    return best;
}
long long bruteTrading(const vector<int>& p, int fee, bool cooldown, int maxSales) {
    const long long NEG = LLONG_MIN/4;
    function<long long(int,bool,int,bool)> dfs = [&](int day,bool holding,int sales,bool blocked) {
        if (day == (int)p.size()) return holding ? NEG : 0LL;
        long long best = dfs(day+1,holding,sales,false); // 今天不操作
        if (holding && sales < maxSales) {
            best = max(best,(long long)p[day]-fee+dfs(day+1,false,sales+1,cooldown));
        } else if (!holding && !blocked && sales < maxSales) {
            long long later = dfs(day+1,true,sales,false);
            if (later != NEG) best = max(best,later-p[day]);
        }
        return best;
    };
    return dfs(0,false,0,false);
}
template<class Exception, class F> void expectThrow(F f) {
    bool thrown = false;
    try { f(); } catch (const Exception&) { thrown = true; }
    assert(thrown);
}
int main() {
    assert(selectIntervals({{1,4},{2,3},{3,5}}).size() == 2);
    assert(selectIntervals({{0,3},{2,4},{3,6}}).size() == 2);
    assert(selectIntervals({}).empty());
    assert(minimumArrowPositions({{1,2},{2,3}}).size() == 1);
    assert(minimumArrowPositions({{INT_MIN,INT_MAX},{INT_MAX,INT_MAX}}).size() == 1);
    assert(minimumArrowPositions({}).empty());
    assert(minimumIntervalCover({{0,2},{0,4},{2,6},{4,7},{6,10}},0,10) == optional<int>(3));
    assert(!minimumIntervalCover({{0,4},{5,10}},0,10));
    assert(minimumIntervalCover({},0,0) == optional<int>(0));
    assert(assignResources({1,2,3},{1,1}) == 1);
    assert(!canReachEnd({}) && canReachEnd({0}));
    assert(!canReachEnd({1,0,2}) && canReachEnd({INT_MAX,0}));
    assert(shortestJumpPath({0}) == optional<vector<int>>(vector<int>{0}));
    assert(!shortestJumpPath({}) && !shortestJumpPath({1,0,2}));
    assert(minJumps({2,3,1,1,4}) == 2 && minJumps({1,0,2}) == -1);
    assert(partitionByteLabels("ababcbacadefegdehijhklij") == vector<int>({9,7,8}));
    assert(partitionByteLabels("").empty());
    string bytes{char(255),'a',char(255)};
    assert(partitionByteLabels(bytes) == vector<int>({3}));
    auto station = gasStationStart({1,2},{2,1}); assert(station && *station == 1);
    assert(!gasStationStart({},{}));
    assert(optimalMergeChecked({1,2,3,4}) == 19);
    assert(optimalMergeChecked({1,100,1}) == 104 && adjacentMergeCost({1,100,1}) == 203);
    assert(optimalMergeChecked({}) == 0 && optimalMergeChecked({LLONG_MAX}) == 0);
    assert(optimalMergeChecked({0,LLONG_MAX}) == LLONG_MAX);
    assert(adjacentMergeCost({}) == 0 && adjacentMergeCost({0}) == 0);
    expectThrow<overflow_error>([] { optimalMergeChecked({1,LLONG_MAX}); });
    // 总权重仍合法，但累计合并费用超过 long long。
    long long big = LLONG_MAX/3;
    expectThrow<overflow_error>([&] { optimalMergeChecked({big,big,big}); });
    expectThrow<invalid_argument>([] { selectIntervals({{2,2}}); });
    expectThrow<invalid_argument>([] { minimumArrowPositions({{2,1}}); });
    expectThrow<invalid_argument>([] { canReachEnd({-1}); });
    expectThrow<invalid_argument>([] { gasStationStart({1},{}); });
    expectThrow<invalid_argument>([] { optimalMergeChecked({-1}); });
    expectThrow<invalid_argument>([] { stockProfitWithFee({1,2},-1); });
    assert(stockProfitOnce({7,1,5,3,6,4}) == 5);
    assert(stockProfitWithFee({1,3,2,8,4,9},2) == 8);
    assert(stockProfitCooldown({1,2,3,0,2}) == 3);
    assert(stockProfitOnce({}) == 0 && stockProfitCooldown({}) == 0);
    assert(stockProfitWithFee({0,INT_MAX,0,INT_MAX},0) == 2LL*INT_MAX);
    mt19937 rng(20260921);
    for (int trial = 0; trial < 100; ++trial) {
        int n = rng()%7;
        vector<pair<int,int>> intervals;
        for (int i = 0; i < n; ++i) {
            int l = (int)(rng()%7)-2, r = l+1+(int)(rng()%4);
            intervals.push_back({l,r});
        }
        auto selected = selectIntervals(intervals);
        assert((int)selected.size() == bruteSchedule(intervals));
        vector<char> used(n,false); long long end = LLONG_MIN;
        for (int id : selected) {
            assert(id >= 0 && id < n && !used[id]); used[id] = true;
            assert(intervals[id].first >= end); end = intervals[id].second;
        }
        auto arrows = minimumArrowPositions(intervals);
        assert((int)arrows.size() == bruteArrows(intervals));
        for (auto [l,r] : intervals) {
            bool hit = false;
            for (int x : arrows) if (l <= x && x <= r) hit = true;
            assert(hit);
        }
        assert(minimumIntervalCover(intervals,0,6) == bruteCover(intervals,0,6));
        vector<int> needs(rng()%6), sizes(rng()%6);
        for (int& x : needs) x = rng()%5;
        for (int& x : sizes) x = rng()%5;
        assert(assignResources(needs,sizes) == bruteResources(needs,sizes));
        vector<int> jumps(n); for (int& x : jumps) x = rng()%5;
        int expected = bruteJumps(jumps);
        assert(canReachEnd(jumps) == (expected >= 0));
        assert(minJumps(jumps) == (jumps.empty() ? 0 : expected));
        auto path = shortestJumpPath(jumps);
        assert(path.has_value() == (expected >= 0));
        if (path) {
            assert(path->front() == 0 && path->back() == n-1);
            assert((int)path->size()-1 == expected);
            for (size_t j = 1; j < path->size(); ++j)
                assert((*path)[j] > (*path)[j-1] && (long long)(*path)[j] <= (long long)(*path)[j-1]+jumps[(*path)[j-1]]);
        }
        string s; for (int i = 0; i < n; ++i) s.push_back(char('a'+rng()%4));
        auto parts = partitionByteLabels(s); assert((int)parts.size() == brutePartitions(s));
        array<int,256> owner; owner.fill(-1); int offset = 0;
        for (int part = 0; part < (int)parts.size(); ++part) {
            assert(parts[part] > 0 && offset+parts[part] <= n);
            for (int j = 0; j < parts[part]; ++j) {
                unsigned char c = (unsigned char)s[offset++];
                assert(owner[c] == -1 || owner[c] == part); owner[c] = part;
            }
        }
        assert(offset == n);
        vector<int> gas(n), cost(n);
        for (int& x : gas) x = rng()%5;
        for (int& x : cost) x = rng()%5;
        bool possible = false;
        for (int start = 0; start < n; ++start) possible = possible || validGasStart(gas,cost,start);
        auto start = gasStationStart(gas,cost);
        assert(start.has_value() == possible); if (start) assert(validGasStart(gas,cost,*start));
        vector<int> weights(rng()%6); for (int& x : weights) x = rng()%8;
        vector<long long> wide(weights.begin(),weights.end());
        assert(optimalMergeChecked(wide) == bruteMerge(wide,false));
        assert(minMergeCost(weights) == optimalMergeChecked(wide));
        assert(adjacentMergeCost(weights) == bruteMerge(wide,true));
        vector<int> prices(n); for (int& x : prices) x = rng()%8;
        int fee = rng()%4;
        assert(stockProfitOnce(prices) == bruteTrading(prices,0,false,1));
        assert(maxProfitUnlimited(prices) == bruteTrading(prices,0,false,n));
        assert(stockProfitWithFee(prices,0) == maxProfitUnlimited(prices));
        assert(stockProfitWithFee(prices,fee) == bruteTrading(prices,fee,false,n));
        assert(stockProfitCooldown(prices) == bruteTrading(prices,0,true,n));
    }
    cout << "greedy checks passed\n";
}
