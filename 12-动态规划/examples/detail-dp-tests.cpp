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

#include "detail-max-subarray-range.cpp"
#include "detail-rob-circle.cpp"
#include "detail-knapsack-exact.cpp"
#include "detail-equal-partition.cpp"
#include "detail-min-coins-path.cpp"
#include "detail-coin-counts.cpp"
#include "detail-lcs-path.cpp"
#include "detail-edit-distance.cpp"
#include "detail-lis-path.cpp"
#include "detail-palindrome-substring.cpp"
#include "detail-burst-balloons.cpp"
#include "detail-tree-rob-iterative.cpp"
#include "detail-stock-k.cpp"
#include "detail-assignment-mask.cpp"
#include "01.cpp"
#include "02.cpp"
#include "03.cpp"
#include "04.cpp"
#include "05.cpp"
#include "06.cpp"

bool isSubsequenceOf(const string& small, const string& large) {
    size_t i = 0;
    for (char c : large) if (i < small.size() && small[i] == c) ++i;
    return i == small.size();
}
bool isPalindromeText(const string& s) {
    string reversed(s.rbegin(),s.rend());
    return s == reversed;
}
string maskString(const string& s, int mask) {
    string result;
    for (int i = 0; i < (int)s.size(); ++i)
        if (mask & (1 << i)) result.push_back(s[i]);
    return result;
}
BestSubarray bruteSubarray(const vector<int>& a) {
    BestSubarray best{LLONG_MIN,0,0};
    for (int l = 0; l < (int)a.size(); ++l) {
        long long sum = 0;
        for (int r = l; r < (int)a.size(); ++r) {
            sum += a[r];
            if (sum > best.sum) best = {sum,l,r};
        }
    }
    return best; // l、r 升序枚举，严格改进自然保持相同平局规则
}
long long bruteRobCircle(const vector<int>& a) {
    int n = (int)a.size();
    long long best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true; long long sum = 0;
        for (int i = 0; i < n; ++i) if (mask & (1 << i)) {
            sum += a[i];
            if (n > 1 && (mask & (1 << ((i+1)%n)))) ok = false;
        }
        if (ok) best = max(best,sum);
    }
    return best;
}
pair<optional<long long>,long long> bruteKnapsack(
    const vector<int>& w, const vector<int>& v, int capacity) {
    optional<long long> exact; long long atMost = 0;
    for (int mask = 0; mask < (1 << w.size()); ++mask) {
        int weight = 0; long long value = 0;
        for (int i = 0; i < (int)w.size(); ++i) if (mask & (1 << i)) {
            weight += w[i]; value += v[i];
        }
        if (weight == capacity && (!exact || value > *exact)) exact = value;
        if (weight <= capacity) atMost = max(atMost,value);
    }
    return {exact,atMost};
}
bool brutePartition(const vector<int>& a) {
    int total = accumulate(a.begin(),a.end(),0);
    for (int mask = 0; mask < (1 << a.size()); ++mask) {
        int sum = 0;
        for (int i = 0; i < (int)a.size(); ++i)
            if (mask & (1 << i)) sum += a[i];
        if (2*sum == total) return true;
    }
    return false;
}
long long bruteCoinCombos(const vector<int>& coins, int index, int remaining) {
    if (index == (int)coins.size()) return remaining == 0 ? 1LL : 0LL;
    long long ways = 0;
    for (int count = 0; count*coins[index] <= remaining; ++count)
        ways += bruteCoinCombos(coins,index+1,remaining-count*coins[index]);
    return ways;
}
long long bruteCoinOrdered(const vector<int>& coins, int remaining) {
    if (!remaining) return 1;
    long long ways = 0;
    for (int c : coins) if (c <= remaining) ways += bruteCoinOrdered(coins,remaining-c);
    return ways;
}
int coinBFS(const vector<int>& coins, int amount) {
    vector<int> distance(amount+1,-1);
    queue<int> q; q.push(0); distance[0] = 0;
    while (!q.empty()) {
        int sum = q.front(); q.pop();
        for (int c : coins) if (sum+c <= amount && distance[sum+c] == -1) {
            distance[sum+c] = distance[sum]+1; q.push(sum+c);
        }
    }
    return distance[amount];
}
int bruteLCS(const string& a, const string& b) {
    int best = 0;
    for (int mask = 0; mask < (1 << a.size()); ++mask) {
        string candidate = maskString(a,mask);
        if (isSubsequenceOf(candidate,b)) best = max(best,(int)candidate.size());
    }
    return best;
}
int recursiveEdit(const string& a, const string& b, int i, int j) {
    if (i == (int)a.size()) return (int)b.size()-j;
    if (j == (int)b.size()) return (int)a.size()-i;
    if (a[i] == b[j]) return recursiveEdit(a,b,i+1,j+1);
    return 1+min({recursiveEdit(a,b,i+1,j),recursiveEdit(a,b,i,j+1),
                  recursiveEdit(a,b,i+1,j+1)});
}
int bruteLIS(const vector<int>& a) {
    int best = 0;
    for (int mask = 0; mask < (1 << a.size()); ++mask) {
        bool ok = true; long long prev = LLONG_MIN; int length = 0;
        for (int i = 0; i < (int)a.size(); ++i) if (mask & (1 << i)) {
            if (a[i] <= prev) ok = false;
            prev = a[i]; ++length;
        }
        if (ok) best = max(best,length);
    }
    return best;
}
int brutePalindromeSubseq(const string& s) {
    int best = 0;
    for (int mask = 0; mask < (1 << s.size()); ++mask) {
        string candidate = maskString(s,mask);
        if (isPalindromeText(candidate)) best = max(best,(int)candidate.size());
    }
    return best;
}
string brutePalindromeSubstring(const string& s) {
    string best;
    for (int l = 0; l < (int)s.size(); ++l)
        for (int len = 1; l+len <= (int)s.size(); ++len) {
            string candidate = s.substr(l,len);
            if (isPalindromeText(candidate) && candidate.size() > best.size()) best = candidate;
        }
    return best;
}
long long bruteBurst(vector<int> a) {
    long long best = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        long long gain = (i == 0 ? 1LL : a[i-1])*a[i]*
                         (i+1 == (int)a.size() ? 1LL : a[i+1]);
        auto next = a; next.erase(next.begin()+i);
        best = max(best,gain+bruteBurst(next));
    }
    return best;
}
long long bruteTreeRob(const vector<int>& value, const vector<int>& parent) {
    int n = (int)value.size(); long long best = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true; long long sum = 0;
        for (int i = 0; i < n; ++i) if (mask & (1 << i)) {
            sum += value[i];
            if (parent[i] >= 0 && (mask & (1 << parent[i]))) ok = false;
        }
        if (ok) best = max(best,sum);
    }
    return best;
}
long long bruteStock(const vector<int>& p, int k) {
    const long long NEG = LLONG_MIN/4;
    function<long long(int,bool,int)> dfs = [&](int day,bool holding,int sold) {
        if (day == (int)p.size()) return holding ? NEG : 0LL;
        long long best = dfs(day+1,holding,sold);
        if (holding && sold < k)
            best = max(best,(long long)p[day]+dfs(day+1,false,sold+1));
        if (!holding && sold < k) {
            long long future = dfs(day+1,true,sold);
            if (future != NEG) best = max(best,future-p[day]);
        }
        return best;
    };
    return dfs(0,false,0);
}
long long bruteAssignment(const vector<vector<int>>& cost) {
    vector<int> order(cost.size()); iota(order.begin(),order.end(),0);
    long long best = LLONG_MAX;
    do {
        long long sum = 0;
        for (int i = 0; i < (int)cost.size(); ++i) sum += cost[i][order[i]];
        best = min(best,sum);
    } while (next_permutation(order.begin(),order.end()));
    return best;
}
template<class F> void expectInvalid(F action) {
    bool thrown = false;
    try { action(); } catch (const invalid_argument&) { thrown = true; }
    assert(thrown);
}
int main() {
    auto negative = maxSubarrayRange({-5,-2,-7});
    assert(negative.sum == -2 && negative.left == 1 && negative.right == 1);
    auto separated = maxSubarrayRange({5,-100,4});
    assert(separated.sum == 5);
    auto tie = maxSubarrayRange({0,0});
    assert(tie.left == 0 && tie.right == 0);
    assert(robCircle({}) == 0 && robCircle({-1}) == 0);
    assert(robCircle({2,3,2}) == 3);
    assert(knapsackExact({2},{-3},2) == optional<long long>(-3));
    assert(!knapsackExact({2},{3},3));
    assert(knapsackExact({}, {},0) == optional<long long>(0));
    assert(knapsack01({2},{3},4) == 3);
    assert(equalPartition({}) && equalPartition({0,0}));
    assert(!equalPartition({1,2,5}));
    assert(minimumCoinsPath({1,3,4},6)->size() == 2);
    assert(!minimumCoinsPath({2},3));
    auto emptyCoins = minimumCoinsPath({},0); assert(emptyCoins && emptyCoins->empty());
    auto counts = coinCountsMod({1,1,2},3);
    assert(counts.first == 2 && counts.second == 3);
    assert(coinCountsMod({1,2},2,2).first == 0); // 可达，但模数结果为零
    assert(oneLCS("abcde","ace") == "ace");
    assert(editDistanceRolling("","abc") == 3);
    assert(editDistanceRolling("horse","ros") == 3);
    assert(strictLISIndices({2,2,2}).size() == 1);
    assert(longestPalindromeSubseq("bbbab") == 4);
    assert(longestPalindromeSubstringDP("bbbab") == "bbb");
    assert(burstBalloonsDP({3,1,5,8}) == 167 && burstBalloonsDP({}) == 0);
    assert(robTreeIterative(nullptr) == 0);
    assert(stockAtMostK({3,2,6,5,0,3},2) == 7);
    assert(stockAtMostK({1,3,2,4},0) == 0);
    assert(stockAtMostK({0,INT_MAX,0,INT_MAX},2) == 2LL*INT_MAX);
    assert(minimumAssignment({{9,2},{3,7}}).first == 5);
    auto noTasks = minimumAssignment({}); assert(noTasks.first == 0 && noTasks.second.empty());
    expectInvalid([] { maxSubarrayRange({}); });
    expectInvalid([] { knapsackExact({0},{1},2); });
    expectInvalid([] { equalPartition({-1,1}); });
    expectInvalid([] { minimumCoinsPath({0},2); });
    expectInvalid([] { coinCountsMod({1},2,1); });
    expectInvalid([] { burstBalloonsDP({1001}); });
    expectInvalid([] { stockAtMostK({1},-1); });
    expectInvalid([] { minimumAssignment({{1,2}}); });

    mt19937 rng(20260921);
    for (int trial = 0; trial < 100; ++trial) {
        int n = (int)(rng()%8);
        vector<int> a(n); for (int& x : a) x = (int)(rng()%11)-5;
        if (n) {
            auto got = maxSubarrayRange(a), want = bruteSubarray(a);
            assert(got.sum == want.sum && got.left == want.left && got.right == want.right);
            assert(maxSubArray(a) == want.sum);
        }
        assert(robCircle(a) == bruteRobCircle(a));
        vector<int> weight(n), value(n), nonnegative(n);
        for (int& x : weight) x = 1+(int)(rng()%4);
        for (int& x : value) x = (int)(rng()%13)-6;
        for (int& x : nonnegative) x = (int)(rng()%5);
        int capacity = (int)(rng()%10);
        auto bag = bruteKnapsack(weight,value,capacity);
        assert(knapsackExact(weight,value,capacity) == bag.first);
        assert(knapsack01(weight,value,capacity) == bag.second);
        assert(equalPartition(nonnegative) == brutePartition(nonnegative));

        vector<int> coins;
        for (int c = 1; c <= 4; ++c) if (rng()%2) coins.push_back(c);
        int amount = (int)(rng()%9);
        auto ways = coinCountsMod(coins,amount,7);
        assert(ways.first == bruteCoinCombos(coins,0,amount)%7);
        assert(ways.second == bruteCoinOrdered(coins,amount)%7);
        assert(coinCombinations(coins,amount) == bruteCoinCombos(coins,0,amount));
        int shortest = coinBFS(coins,amount);
        auto path = minimumCoinsPath(coins,amount);
        assert(path.has_value() == (shortest != -1));
        if (path) {
            assert((int)path->size() == shortest);
            assert(accumulate(path->begin(),path->end(),0) == amount);
            for (int c : *path) assert(find(coins.begin(),coins.end(),c) != coins.end());
        }

        string s,t;
        for (int i = 0; i < n; ++i) s.push_back(char('a'+rng()%3));
        int m = (int)(rng()%6);
        for (int i = 0; i < m; ++i) t.push_back(char('a'+rng()%3));
        auto common = oneLCS(s,t);
        assert(isSubsequenceOf(common,s) && isSubsequenceOf(common,t));
        assert((int)common.size() == bruteLCS(s,t));
        assert(longestCommonSubsequence(s,t) == (int)common.size());
        assert(editDistanceRolling(s,t) == recursiveEdit(s,t,0,0));
        assert(editDistanceRolling(s,t) == editDistanceRolling(t,s));
        auto lis = strictLISIndices(a);
        assert((int)lis.size() == bruteLIS(a));
        for (int i = 0; i < (int)lis.size(); ++i) {
            assert(lis[i] >= 0 && lis[i] < n);
            if (i) assert(lis[i-1] < lis[i] && a[lis[i-1]] < a[lis[i]]);
        }
        assert(longestPalindromeSubseq(s) == brutePalindromeSubseq(s));
        assert(longestPalindromeSubstringDP(s) == brutePalindromeSubstring(s));
        vector<int> balloons(rng()%6);
        for (int& x : balloons) x = (int)(rng()%5);
        assert(burstBalloonsDP(balloons) == bruteBurst(balloons));

        vector<RobNode> nodes; vector<TreeNode> basicNodes;
        nodes.reserve(n); basicNodes.reserve(n);
        vector<int> parent(n,-1);
        for (int x : a) { nodes.emplace_back(x); basicNodes.emplace_back(x); }
        for (int i = 1; i < n; ++i) {
            parent[i] = (i-1)/2;
            if (i%2) {
                nodes[parent[i]].left = &nodes[i];
                basicNodes[parent[i]].left = &basicNodes[i];
            } else {
                nodes[parent[i]].right = &nodes[i];
                basicNodes[parent[i]].right = &basicNodes[i];
            }
        }
        long long treeBest = bruteTreeRob(a,parent);
        assert(robTreeIterative(n ? &nodes[0] : nullptr) == treeBest);
        assert(robTree(n ? &basicNodes[0] : nullptr) == treeBest);
        int k = (int)(rng()%4);
        assert(stockAtMostK(nonnegative,k) == bruteStock(nonnegative,k));
        int jobs = (int)(rng()%7);
        vector<vector<int>> cost(jobs,vector<int>(jobs));
        for (auto& row : cost) for (int& x : row) x = (int)(rng()%15)-7;
        auto assignment = minimumAssignment(cost);
        assert(assignment.first == bruteAssignment(cost));
        assert((int)assignment.second.size() == jobs);
        vector<char> used(jobs,false); long long actual = 0;
        for (int worker = 0; worker < jobs; ++worker) {
            int task = assignment.second[worker];
            assert(task >= 0 && task < jobs && !used[task]);
            used[task] = true; actual += cost[worker][task];
        }
        assert(actual == assignment.first);
    }
    vector<RobNode> chain; chain.reserve(5000);
    for (int i = 0; i < 5000; ++i) chain.emplace_back(1);
    for (int i = 1; i < 5000; ++i) chain[i-1].right = &chain[i];
    assert(robTreeIterative(&chain[0]) == 2500);
    cout << "dynamic programming checks passed\n";
}
