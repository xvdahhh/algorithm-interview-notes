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

class FrequencyFenwick {
    int n;
    vector<long long> bit, frequency;
    long long total = 0;
public:
    explicit FrequencyFenwick(int size): n(size) {
        if (n < 0 || n > 1000000) throw invalid_argument("size");
        bit.assign(n+1,0); frequency.assign(n,0);
    }
    void add(int p, long long delta) {
        if (p < 0 || p >= n) throw out_of_range("index");
        if (delta < 0 && delta < -frequency[p]) throw invalid_argument("negative frequency");
        if (delta > 0 && total > LLONG_MAX-delta) throw overflow_error("total");
        frequency[p] += delta; total += delta;
        for (int i = p+1; i <= n; i += i&-i) bit[i] += delta;
    }
    optional<int> kth(long long k) const {
        if (k < 1 || k > total) return nullopt;
        int index = 0, step = 1;
        while (step <= n/2) step *= 2;
        for (; step > 0; step /= 2) {
            int next = index+step;
            if (next <= n && bit[next] < k) {
                index = next; k -= bit[next];
            }
        }
        return index; // 已跳过 index 项，下一个一基位置对应零基 index
    }
    long long count() const { return total; }
};
