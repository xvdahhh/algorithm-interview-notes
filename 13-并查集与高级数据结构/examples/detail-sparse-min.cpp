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

class SparseMinimum {
    int n;
    vector<int> logs;
    vector<vector<int>> table;
public:
    explicit SparseMinimum(const vector<int>& a): n((int)a.size()) {
        if (a.size() > 1000000) throw invalid_argument("size limit");
        logs.assign(n+1,0);
        for (int i = 2; i <= n; ++i) logs[i] = logs[i/2]+1;
        if (!n) return;
        table.push_back(a);
        for (int k = 1; k <= logs[n]; ++k) {
            int length = 1 << k, half = length/2;
            table.push_back(vector<int>(n-length+1));
            for (int i = 0; i+length <= n; ++i)
                table[k][i] = min(table[k-1][i],table[k-1][i+half]);
        }
    }
    optional<int> minimum(int l, int r) const {
        if (l < 0 || r < l || r > n) throw out_of_range("range");
        if (l == r) return nullopt;
        int k = logs[r-l], length = 1 << k;
        return min(table[k][l],table[k][r-length]);
    }
};
