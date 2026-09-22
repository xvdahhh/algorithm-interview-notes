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

#include "detail-lru-optional.cpp"
#include "detail-lfu-cache.cpp"
#include "detail-topk-frequency.cpp"
#include "detail-peak-intervals.cpp"
#include "detail-room-assignment.cpp"
#include "detail-car-pooling.cpp"
#include "detail-randomized-multiset.cpp"
#include "detail-reservoir.cpp"
#include "detail-shuffle.cpp"
#include "detail-safe-gcd-lcm.cpp"
#include "detail-modular-arithmetic.cpp"
#include "detail-smallest-prime.cpp"
#include "01.cpp"
#include "02.cpp"
#include "03.cpp"
#include "04.cpp"

class SlowLRU {
    size_t capacity;
    vector<pair<int,int>> data; // 最近使用在前
public:
    explicit SlowLRU(int cap): capacity(cap) {}
    optional<int> get(int key) {
        for (size_t i = 0; i < data.size(); ++i) if (data[i].first == key) {
            auto item = data[i]; data.erase(data.begin()+i); data.insert(data.begin(),item);
            return item.second;
        }
        return nullopt;
    }
    void put(int key, int value) {
        erase(key);
        if (capacity) data.insert(data.begin(),{key,value});
        if (data.size() > capacity) data.pop_back();
    }
    bool erase(int key) {
        for (size_t i = 0; i < data.size(); ++i) if (data[i].first == key) {
            data.erase(data.begin()+i); return true;
        }
        return false;
    }
    void resize(int cap) { capacity = cap; if (data.size() > capacity) data.resize(capacity); }
    size_t size() const { return data.size(); }
};
class SlowLFU {
    struct Item { int value, frequency, lastUse; };
    int capacity, clock = 0;
    unordered_map<int,Item> data;
public:
    explicit SlowLFU(int cap): capacity(cap) {}
    optional<int> get(int key) {
        auto it = data.find(key);
        if (it == data.end()) return nullopt;
        ++it->second.frequency; it->second.lastUse = ++clock; return it->second.value;
    }
    void put(int key, int value) {
        auto it = data.find(key);
        if (it != data.end()) {
            it->second.value = value; ++it->second.frequency; it->second.lastUse = ++clock; return;
        }
        if (!capacity) return;
        if ((int)data.size() == capacity) {
            auto victim = data.begin();
            for (auto candidate = data.begin(); candidate != data.end(); ++candidate)
                if (make_pair(candidate->second.frequency,candidate->second.lastUse) <
                    make_pair(victim->second.frequency,victim->second.lastUse)) victim = candidate;
            data.erase(victim);
        }
        data[key] = {value,1,++clock};
    }
    size_t size() const { return data.size(); }
};
PeakConcurrency brutePeak(const vector<pair<int,int>>& intervals) {
    vector<int> points;
    for (auto [l,r] : intervals) if (l < r) { points.push_back(l); points.push_back(r); }
    sort(points.begin(),points.end()); points.erase(unique(points.begin(),points.end()),points.end());
    PeakConcurrency result;
    for (size_t i = 1; i < points.size(); ++i) {
        int l = points[i-1], r = points[i], active = 0;
        for (auto interval : intervals) if (interval.first <= l && l < interval.second) ++active;
        if (active > result.count) { result.count = active; result.spans.clear(); }
        if (active > 0 && active == result.count) {
            if (!result.spans.empty() && result.spans.back().second == l) result.spans.back().second = r;
            else result.spans.push_back({l,r});
        }
    }
    return result;
}
bool bruteCarPool(const vector<array<int,3>>& trips, long long capacity) {
    for (auto event : trips) {
        int position = event[1]; long long passengers = 0;
        for (auto trip : trips)
            if (trip[1] <= position && position < trip[2]) passengers += trip[0];
        if (passengers > capacity) return false;
    }
    return true;
}
vector<int> bruteTopK(const vector<int>& a, int k) {
    unordered_map<int,int> counts;
    for (int x : a) ++counts[x];
    vector<int> values; for (auto item : counts) values.push_back(item.first);
    sort(values.begin(),values.end(),[&](int x,int y) {
        if (counts[x] != counts[y]) return counts[x] > counts[y];
        return x < y;
    });
    values.resize(k); return values;
}
bool trialPrime(int x) {
    if (x < 2) return false;
    for (int divisor = 2; divisor <= x/divisor; ++divisor)
        if (x%divisor == 0) return false;
    return true;
}
template<class Exception, class F> void expectException(F action) {
    bool caught = false;
    try { action(); } catch (const Exception&) { caught = true; }
    assert(caught);
}
int main() {
    OptionalLRU lru(2); lru.put(1,-1); lru.put(2,20);
    assert(lru.get(1) == optional<int>(-1)); lru.put(3,30);
    assert(!lru.get(2)); lru.resize(0); lru.put(4,40); assert(lru.size() == 0);
    expectException<invalid_argument>([&] { lru.resize(-1); });
    LFUCacheExample lfu(2); lfu.put(1,1); lfu.put(2,2);
    assert(lfu.get(1) == optional<int>(1)); lfu.put(3,3);
    assert(!lfu.get(2)); assert(lfu.get(3) == optional<int>(3));
    lfu.put(4,4); assert(!lfu.get(1)); // 1、3 同频，1 更旧
    LFUCacheExample disabled(0); disabled.put(1,1); assert(!disabled.get(1));
    LRUCache basicLRU(1); basicLRU.put(1,2); basicLRU.put(3,4);
    assert(basicLRU.get(1) == -1 && basicLRU.get(3) == 4);
    assert(topKFrequentStable({2,1,2,1,3},2) == vector<int>({1,2}));
    assert(topKFrequentStable({},0).empty());
    expectException<invalid_argument>([] { topKFrequentStable({1},2); });
    auto peak = peakConcurrency({{0,10},{5,10},{10,15}});
    assert((peak.count == 2 && peak.spans == vector<pair<int,int>>({{5,10}})));
    auto continuous = peakConcurrency({{0,1},{1,2}});
    assert((continuous.spans == vector<pair<int,int>>({{0,2}})));
    assert(peakConcurrency({{2,2}}).spans.empty());
    assert(assignMeetingRooms({{1,1}}).roomForMeeting == vector<int>({-1}));
    assert(canCarPool({{2,0,5},{2,5,10}},2));
    expectException<invalid_argument>([] { peakConcurrency({{2,1}}); });
    RandomizedMultisetExample multiset;
    assert(!multiset.getRandom());
    assert(multiset.insert(5) && !multiset.insert(5) && multiset.insert(7));
    assert(multiset.eraseOne(7) && multiset.eraseOne(5) && multiset.count(5) == 1);
    assert(multiset.getRandom() == optional<int>(5));
    assert(multiset.eraseOne(5) && !multiset.eraseOne(5) && !multiset.getRandom());
    RandomizedSet basicSet; assert(basicSet.insert(2) && !basicSet.insert(2));
    assert(basicSet.getRandom() == 2 && basicSet.remove(2));
    expectException<out_of_range>([&] { basicSet.getRandom(); });
    ReservoirSample zero(0); zero.offer(1); assert(zero.processed() == 1 && zero.snapshot().empty());
    expectException<invalid_argument>([] { ReservoirSample invalid(-1); });
    assert(gcdMagnitude(0,0) == 0 && gcdMagnitude(-12,18) == 6);
    assert(gcdMagnitude(LLONG_MIN,0) == (uint64_t(1) << 63));
    assert(lcmMagnitude(LLONG_MIN,1) == optional<uint64_t>(uint64_t(1) << 63));
    assert(lcmMagnitude(0,LLONG_MIN) == optional<uint64_t>(0));
    assert(!lcmMagnitude(LLONG_MAX,LLONG_MAX-1));
    assert(multiplyMod(UINT64_MAX-1,UINT64_MAX-1,UINT64_MAX) == 1);
    assert(multiplyMod(UINT64_MAX-2,UINT64_MAX-3,UINT64_MAX) == 6);
    assert(powerMod(UINT64_MAX-1,2,UINT64_MAX) == 1);
    assert(powerMod(0,0,7) == 1 && powerMod(7,0,1) == 0);
    assert(inverseModSmall(3,7) == optional<long long>(5));
    assert(inverseModSmall(-2,9) == optional<long long>(4));
    assert(!inverseModSmall(2,6) && !inverseModSmall(0,7));
    expectException<invalid_argument>([] { multiplyMod(1,2,0); });
    expectException<invalid_argument>([] { inverseModSmall(1,1); });

    // 枚举抽取下标的选择路径，演示小规模均匀性，不是统计检验 PRNG。
    unordered_map<string,int> permutations;
    function<void(vector<int>,int)> enumerateShuffle = [&](vector<int> a,int remaining) {
        if (remaining <= 1) {
            string key; for (int x : a) key += to_string(x);
            ++permutations[key]; return;
        }
        for (int j = 0; j < remaining; ++j) {
            auto next = a; swap(next[remaining-1],next[j]);
            enumerateShuffle(next,remaining-1);
        }
    };
    enumerateShuffle({0,1,2},3);
    assert(permutations.size() == 6);
    for (auto item : permutations) assert(item.second == 1);
    vector<int> subsetCounts(16);
    for (int j3 = 0; j3 < 3; ++j3) for (int j4 = 0; j4 < 4; ++j4) {
        vector<int> sample{0,1};
        if (j3 < 2) sample[j3] = 2;
        if (j4 < 2) sample[j4] = 3;
        ++subsetCounts[(1 << sample[0]) | (1 << sample[1])];
    }
    for (int mask = 0; mask < 16; ++mask) {
        int count = 0; for (int b = 0; b < 4; ++b) count += (mask >> b)&1;
        assert(subsetCounts[mask] == (count == 2 ? 2 : 0));
    }

    mt19937 rng(20260922);
    for (int trial = 0; trial < 80; ++trial) {
        int cap = (int)(rng()%5);
        OptionalLRU fastLRU(cap); SlowLRU slowLRU(cap);
        LFUCacheExample fastLFU(cap); SlowLFU slowLFU(cap);
        RandomizedMultisetExample randomBag((uint32_t)trial);
        unordered_map<int,int> bag; int bagSize = 0;
        for (int step = 0; step < 60; ++step) {
            int key = (int)(rng()%7)-3, value = (int)(rng()%11)-5;
            switch (rng()%4) {
                case 0: fastLRU.put(key,value); slowLRU.put(key,value); break;
                case 1: assert(fastLRU.get(key) == slowLRU.get(key)); break;
                case 2: assert(fastLRU.erase(key) == slowLRU.erase(key)); break;
                default: {
                    int nextCap = (int)(rng()%5); fastLRU.resize(nextCap); slowLRU.resize(nextCap);
                }
            }
            assert(fastLRU.size() == slowLRU.size());
            if (rng()%2) { fastLFU.put(key,value); slowLFU.put(key,value); }
            else assert(fastLFU.get(key) == slowLFU.get(key));
            assert(fastLFU.size() == slowLFU.size());
            // 固定顺序读一遍：两侧同样刷新，以核对所有逻辑键。
            for (int probe = -3; probe <= 3; ++probe) {
                assert(fastLRU.get(probe) == slowLRU.get(probe));
                assert(fastLFU.get(probe) == slowLFU.get(probe));
            }
            if (rng()%2) { assert(randomBag.insert(key) == (bag[key] == 0)); ++bag[key]; ++bagSize; }
            else {
                bool exists = bag[key] > 0; assert(randomBag.eraseOne(key) == exists);
                if (exists) { --bag[key]; --bagSize; }
            }
            assert(randomBag.size() == (size_t)bagSize);
            for (int probe = -3; probe <= 3; ++probe) assert(randomBag.count(probe) == (size_t)bag[probe]);
            auto draw = randomBag.getRandom();
            assert(draw.has_value() == (bagSize > 0));
            if (draw) assert(bag[*draw] > 0);
        }
        vector<int> a(rng()%20); for (int& x : a) x = (int)(rng()%7)-3;
        int distinct = (int)unordered_set<int>(a.begin(),a.end()).size();
        for (int k = 0; k <= distinct; ++k) assert(topKFrequentStable(a,k) == bruteTopK(a,k));
        vector<pair<int,int>> intervals;
        vector<array<int,3>> trips;
        int count = (int)(rng()%9);
        for (int i = 0; i < count; ++i) {
            int l = (int)(rng()%9)-4, r = l+(int)(rng()%5);
            intervals.push_back({l,r}); trips.push_back({(int)(rng()%5),l,r});
        }
        auto fastPeak = peakConcurrency(intervals), slowPeak = brutePeak(intervals);
        assert(fastPeak.count == slowPeak.count && fastPeak.spans == slowPeak.spans);
        assert(minMeetingRooms(intervals) == slowPeak.count);
        auto assigned = assignMeetingRooms(intervals);
        assert(assigned.rooms == slowPeak.count && assigned.roomForMeeting.size() == intervals.size());
        for (int i = 0; i < count; ++i) {
            if (intervals[i].first == intervals[i].second) assert(assigned.roomForMeeting[i] == -1);
            else assert(assigned.roomForMeeting[i] >= 0 && assigned.roomForMeeting[i] < assigned.rooms);
            for (int j = 0; j < i; ++j)
                if (assigned.roomForMeeting[i] >= 0 && assigned.roomForMeeting[i] == assigned.roomForMeeting[j])
                    assert(intervals[i].second <= intervals[j].first || intervals[j].second <= intervals[i].first);
        }
        long long capacity = rng()%12; assert(canCarPool(trips,capacity) == bruteCarPool(trips,capacity));
        int k = (int)(rng()%25);
        ReservoirSample sample(k,(uint32_t)trial), replay(k,(uint32_t)trial);
        for (int i = 0; i < 20; ++i) { sample.offer(i); replay.offer(i); }
        auto selected = sample.snapshot();
        assert(sample.processed() == 20 && selected == replay.snapshot());
        assert(selected.size() == (size_t)min(k,20));
        unordered_set<int> unique(selected.begin(),selected.end()); assert(unique.size() == selected.size());
        for (int x : selected) assert(x >= 0 && x < 20);
        auto shuffled = a, duplicate = a;
        mt19937 engine((uint32_t)trial), again((uint32_t)trial);
        fisherYatesShuffle(shuffled,engine); fisherYatesShuffle(duplicate,again); assert(shuffled == duplicate);
        sort(shuffled.begin(),shuffled.end()); sort(a.begin(),a.end()); assert(shuffled == a);
        uint64_t x = rng()%1000000, y = rng()%1000000, mod = 1+rng()%1000;
        assert(multiplyMod(x,y,mod) == (x*y)%mod);
        uint64_t exponent = rng()%13, expectedPower = 1%mod;
        for (uint64_t i = 0; i < exponent; ++i) expectedPower = expectedPower*(x%mod)%mod;
        assert(powerMod(x,exponent,mod) == expectedPower);
        uint64_t wide = (uint64_t(rng()) << 32) | rng(), reduced = wide%UINT64_MAX;
        assert(multiplyMod(wide,UINT64_MAX-1,UINT64_MAX) == (reduced ? UINT64_MAX-reduced : 0));
    }
    for (long long a = -30; a <= 30; ++a) for (long long b = -30; b <= 30; ++b) {
        assert(gcdMagnitude(a,b) == (uint64_t)gcd(a,b));
        assert(lcmMagnitude(a,b) == optional<uint64_t>((uint64_t)lcm(a,b)));
    }
    for (long long mod = 2; mod <= 35; ++mod) for (long long a = -35; a <= 35; ++a) {
        optional<long long> expected;
        long long normalized = (a%mod+mod)%mod;
        for (long long x = 0; x < mod; ++x) if (normalized*x%mod == 1) expected = x;
        assert(inverseModSmall(a,mod) == expected);
    }
    for (int n = 0; n <= 120; ++n) {
        SmallestPrimeTable table(n);
        assert(table.primes() == primesUpTo(n));
        for (int x = 0; x <= n; ++x) assert(table.isPrime(x) == trialPrime(x));
        for (int x = 1; x <= n; ++x) {
            auto factors = table.factorize(x); long long product = 1; int previous = 1;
            for (auto [p,e] : factors) {
                assert(p > previous && trialPrime(p) && e > 0); previous = p;
                for (int i = 0; i < e; ++i) product *= p;
            }
            assert(product == x);
        }
    }
    SmallestPrimeTable table(10);
    expectException<out_of_range>([&] { table.factorize(0); });
    cout << "combined technique checks passed\n";
}
