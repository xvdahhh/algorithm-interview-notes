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

#include "detail-dsu-checked.cpp"
#include "detail-online-islands.cpp"
#include "detail-rollback-dsu.cpp"
#include "detail-counting-trie.cpp"
#include "detail-binary-trie.cpp"
#include "detail-fenwick-zero.cpp"
#include "detail-count-smaller.cpp"
#include "detail-range-fenwick.cpp"
#include "detail-fenwick-order.cpp"
#include "detail-lazy-segment.cpp"
#include "detail-max-subarray-tree.cpp"
#include "detail-sparse-min.cpp"
#include "01.cpp"
#include "02.cpp"
#include "03.cpp"
#include "04.cpp"

void modelUnite(vector<int>& label, int a, int b) {
    int old = label[b], replacement = label[a];
    for (int& x : label) if (x == old) x = replacement;
}
int modelGroups(const vector<int>& label) {
    return (int)unordered_set<int>(label.begin(),label.end()).size();
}
int countIslandsModel(const vector<vector<int>>& grid) {
    int rows = (int)grid.size(), cols = (int)grid[0].size(), count = 0;
    vector<vector<char>> seen(rows,vector<char>(cols,false));
    const int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
    for (int r = 0; r < rows; ++r) for (int c = 0; c < cols; ++c) {
        if (!grid[r][c] || seen[r][c]) continue;
        ++count; queue<pair<int,int>> q; q.push({r,c}); seen[r][c] = true;
        while (!q.empty()) {
            auto [x,y] = q.front(); q.pop();
            for (int k = 0; k < 4; ++k) {
                int nx = x+dr[k], ny = y+dc[k];
                if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) continue;
                if (grid[nx][ny] && !seen[nx][ny]) { seen[nx][ny] = true; q.push({nx,ny}); }
            }
        }
    }
    return count;
}
bool wordMatches(const string& word, const string& pattern) {
    if (word.size() != pattern.size()) return false;
    for (size_t i = 0; i < word.size(); ++i)
        if (pattern[i] != '.' && pattern[i] != word[i]) return false;
    return true;
}
optional<long long> bruteBest(const vector<int>& a, int l, int r) {
    if (l == r) return nullopt;
    long long best = LLONG_MIN;
    for (int i = l; i < r; ++i) {
        long long sum = 0;
        for (int j = i; j < r; ++j) { sum += a[j]; best = max(best,sum); }
    }
    return best;
}
template<class Exception, class F> void expectException(F action) {
    bool caught = false;
    try { action(); } catch (const Exception&) { caught = true; }
    assert(caught);
}
int main() {
    assert(CheckedDSU(0).count() == 0 && RollbackDSU(0).count() == 0);
    expectException<invalid_argument>([] { CheckedDSU bad(-1); });
    CheckedDSU isolated(2);
    expectException<out_of_range>([&] { isolated.unite(0,2); });
    assert(isolated.count() == 2);
    RollbackDSU rollback(3);
    auto empty = rollback.snapshot();
    rollback.unite(0,1); auto middle = rollback.snapshot();
    assert(!rollback.unite(0,1) && rollback.snapshot() == middle);
    rollback.unite(1,2); rollback.rollback(middle);
    assert(rollback.count() == 2 && rollback.find(0) != rollback.find(2));
    rollback.rollback(empty); assert(rollback.count() == 3);
    expectException<out_of_range>([&] { rollback.rollback(1); });
    assert(islandCountsAfterAdds(2,2,{{0,0},{0,1},{1,0},{1,1},{1,1}}) ==
           vector<int>({1,1,1,1,1}));
    assert(islandCountsAfterAdds(0,0,{}).empty());

    CountingTrie words;
    words.insert("apple"); words.insert("apple"); words.insert("app");
    assert(words.countPrefix("app") == 3 && words.countWord("app") == 1);
    assert(words.eraseOne("apple") && words.countWord("apple") == 1);
    assert(words.eraseOne("apple") && !words.matches("a...."));
    assert(!words.eraseOne("apple") && words.countPrefix("app") == 1);
    words.insert(""); assert(words.matches("") && words.countPrefix("") == 2);
    assert(words.matches("...") && !words.matches(".."));
    expectException<invalid_argument>([&] { words.insert("ap!"); });
    assert(words.countPrefix("") == 2);
    assert(words.eraseOne("") && !words.matches(""));
    Trie basicWords; basicWords.insert("apple");
    assert(basicWords.startsWith("app") && !basicWords.search("app"));
    basicWords.insert("app"); assert(basicWords.search("app"));
    BinaryTrie32 binary;
    assert(!binary.maxXor(0));
    binary.insert(0); binary.insert(uint32_t(1) << 31);
    assert(binary.maxXor(0) == optional<uint32_t>(uint32_t(1) << 31));
    binary.insert(UINT32_MAX); assert(binary.maxXor(0) == optional<uint32_t>(UINT32_MAX));

    FenwickZero zero(vector<long long>{});
    assert(zero.rangeSum(0,0) == 0);
    expectException<out_of_range>([&] { zero.add(0,1); });
    RangeAddFenwick noRange(0); noRange.add(0,0,5); assert(noRange.rangeSum(0,0) == 0);
    LazyRangeSum noLazy(vector<long long>{}); noLazy.assign(0,0,2);
    assert(noLazy.sum(0,0) == 0);
    MaxSubarrayTree noMax(vector<int>{}); assert(!noMax.best(0,0));
    SparseMinimum noMin(vector<int>{}); assert(!noMin.minimum(0,0));
    LazyRangeSum lazy({1,2,3,4});
    lazy.add(0,4,3); lazy.assign(1,3,0); lazy.add(2,4,2);
    assert(lazy.sum(0,4) == 15 && lazy.sum(1,3) == 2 && lazy.sum(3,4) == 9);
    lazy.assign(0,4,2); lazy.add(0,4,3); assert(lazy.sum(0,4) == 20);
    lazy.add(0,4,3); lazy.assign(0,4,2); assert(lazy.sum(0,4) == 8);
    assert(MaxSubarrayTree({-4,-2,-8}).best(0,3) == optional<long long>(-2));
    assert(countSmallerRight({5,2,6,1}) == vector<int>({2,1,1,0}));
    assert(countSmallerRight({2,2,2}) == vector<int>({0,0,0}));
    FrequencyFenwick frequencies(4);
    frequencies.add(1,2); frequencies.add(3,1);
    assert(!frequencies.kth(0) && !frequencies.kth(4));
    assert(frequencies.kth(1) == optional<int>(1) && frequencies.kth(2) == optional<int>(1));
    assert(frequencies.kth(3) == optional<int>(3));
    expectException<invalid_argument>([&] { frequencies.add(1,-3); });
    assert(frequencies.count() == 3);
    FrequencyFenwick large(1); large.add(0,LLONG_MAX);
    assert(large.kth(LLONG_MAX) == optional<int>(0));
    expectException<overflow_error>([&] { large.add(0,1); });
    expectException<invalid_argument>([&] { large.add(0,LLONG_MIN); });
    assert(large.count() == LLONG_MAX);

    mt19937 rng(20260922);
    auto randomWord = [&]() {
        string s; int length = (int)(rng()%5);
        for (int i = 0; i < length; ++i) s.push_back(char('a'+rng()%3));
        return s;
    };
    for (int trial = 0; trial < 80; ++trial) {
        int n = 1+(int)(rng()%8);
        CheckedDSU dsu(n); UnionFind basicDsu(n);
        vector<int> label(n); iota(label.begin(),label.end(),0);
        for (int step = 0; step < 40; ++step) {
            int a = (int)(rng()%n), b = (int)(rng()%n);
            bool expected = label[a] != label[b];
            assert(dsu.unite(a,b) == expected && basicDsu.unite(a,b) == expected);
            modelUnite(label,a,b);
            assert(dsu.count() == modelGroups(label) && basicDsu.count() == modelGroups(label));
            for (int i = 0; i < n; ++i) {
                assert(dsu.componentSize(i) == count(label.begin(),label.end(),label[i]));
                for (int j = 0; j < n; ++j)
                    assert(dsu.connected(i,j) == (label[i] == label[j]));
            }
        }
        RollbackDSU history(n);
        iota(label.begin(),label.end(),0);
        vector<pair<size_t,vector<int>>> snapshots{{history.snapshot(),label}};
        for (int step = 0; step < 50; ++step) {
            int op = (int)(rng()%4);
            if (op == 0) snapshots.push_back({history.snapshot(),label});
            else if (op == 1) {
                size_t which = rng()%snapshots.size();
                history.rollback(snapshots[which].first); label = snapshots[which].second;
                snapshots.resize(which+1);
            } else {
                int a = (int)(rng()%n), b = (int)(rng()%n);
                assert(history.unite(a,b) == (label[a] != label[b]));
                modelUnite(label,a,b);
            }
            assert(history.count() == modelGroups(label));
            for (int i = 0; i < n; ++i) {
                assert(history.componentSize(i) == count(label.begin(),label.end(),label[i]));
                for (int j = 0; j < n; ++j)
                    assert((history.find(i) == history.find(j)) == (label[i] == label[j]));
            }
        }
        vector<vector<int>> grid(3,vector<int>(4,0));
        vector<pair<int,int>> positions; vector<int> counts;
        for (int step = 0; step < 20; ++step) {
            int r = (int)(rng()%3), c = (int)(rng()%4);
            positions.push_back({r,c}); grid[r][c] = 1; counts.push_back(countIslandsModel(grid));
        }
        assert(islandCountsAfterAdds(3,4,positions) == counts);

        CountingTrie trie; unordered_map<string,int> dictionary;
        BinaryTrie32 xorTrie; vector<uint32_t> numbers;
        for (int step = 0; step < 40; ++step) {
            string word = randomWord();
            if (rng()%2) { trie.insert(word); ++dictionary[word]; }
            else {
                bool exists = dictionary[word] > 0;
                assert(trie.eraseOne(word) == exists);
                if (exists) --dictionary[word];
            }
            assert(trie.countWord(word) == dictionary[word]);
            string prefix = word.substr(0,word.size()/2);
            long long expectedPrefix = 0;
            for (const auto& item : dictionary)
                if (item.first.compare(0,prefix.size(),prefix) == 0) expectedPrefix += item.second;
            assert(trie.countPrefix(prefix) == expectedPrefix);
            string pattern = randomWord();
            for (char& c : pattern) if (rng()%2) c = '.';
            bool expectedMatch = false;
            for (const auto& item : dictionary)
                if (item.second > 0 && wordMatches(item.first,pattern)) expectedMatch = true;
            assert(trie.matches(pattern) == expectedMatch);
            uint32_t x = (uint32_t)rng(); xorTrie.insert(x); numbers.push_back(x);
            uint32_t query = (uint32_t)rng(), best = 0;
            for (uint32_t number : numbers) best = max(best,query^number);
            assert(xorTrie.maxXor(query) == optional<uint32_t>(best));
        }

        vector<long long> values(n);
        vector<int> integerValues(n);
        for (int i = 0; i < n; ++i) values[i] = integerValues[i] = (int)(rng()%21)-10;
        FenwickZero fenwick(values); Fenwick basicFenwick(n);
        for (int i = 0; i < n; ++i) basicFenwick.add(i+1,values[i]);
        SegmentTree basicSegment(integerValues);
        MaxSubarrayTree maxTree(integerValues);
        SparseMinimum sparse(integerValues);
        for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
            optional<int> want;
            if (l < r) want = *min_element(integerValues.begin()+l,integerValues.begin()+r);
            assert(sparse.minimum(l,r) == want);
        }
        RangeAddFenwick rangeTree(n); LazyRangeSum lazyTree(vector<long long>(n,0));
        vector<long long> rangeModel(n,0);
        FrequencyFenwick order(n); vector<long long> frequency(n,0);
        for (int step = 0; step < 40; ++step) {
            int p = (int)(rng()%n), value = (int)(rng()%21)-10;
            long long delta = value-values[p];
            if (rng()%2) fenwick.setValue(p,value); else fenwick.add(p,delta);
            basicFenwick.add(p+1,delta); basicSegment.setValue(p,value);
            maxTree.setValue(p,value); values[p] = integerValues[p] = value;
            int l = (int)(rng()%(n+1)), r = (int)(rng()%(n+1));
            if (l > r) swap(l,r);
            long long change = (int)(rng()%11)-5;
            if (rng()%2) {
                lazyTree.add(l,r,change); rangeTree.add(l,r,change);
                for (int i = l; i < r; ++i) rangeModel[i] += change;
            } else {
                lazyTree.assign(l,r,change);
                for (int i = l; i < r; ++i) {
                    rangeTree.add(i,i+1,change-rangeModel[i]); rangeModel[i] = change;
                }
            }
            for (int left = 0; left <= n; ++left) for (int right = left; right <= n; ++right) {
                long long sum = accumulate(values.begin()+left,values.begin()+right,0LL);
                assert(fenwick.rangeSum(left,right) == sum && basicSegment.query(left,right) == sum);
                assert(basicFenwick.prefix(right)-basicFenwick.prefix(left) == sum);
                assert(maxTree.best(left,right) == bruteBest(integerValues,left,right));
                long long rangeSum = accumulate(rangeModel.begin()+left,rangeModel.begin()+right,0LL);
                assert(lazyTree.sum(left,right) == rangeSum && rangeTree.rangeSum(left,right) == rangeSum);
            }
            int index = (int)(rng()%n);
            long long amount = frequency[index] > 0 && rng()%2 ? -1 : 1;
            order.add(index,amount); frequency[index] += amount;
            long long total = accumulate(frequency.begin(),frequency.end(),0LL);
            assert(order.count() == total && !order.kth(0) && !order.kth(total+1));
            for (long long k = 1; k <= total; ++k) {
                long long prefix = 0; int expected = 0;
                while (prefix+frequency[expected] < k) prefix += frequency[expected++];
                assert(order.kth(k) == optional<int>(expected));
            }
        }
        auto smaller = countSmallerRight(integerValues);
        for (int i = 0; i < n; ++i) {
            int expected = 0;
            for (int j = i+1; j < n; ++j) expected += integerValues[j] < integerValues[i];
            assert(smaller[i] == expected);
        }
    }
    cout << "advanced data structure checks passed\n";
}
