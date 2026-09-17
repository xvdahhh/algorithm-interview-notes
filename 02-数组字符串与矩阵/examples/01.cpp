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

vector<vector<int>> threeSum(vector<int> a) {
    sort(a.begin(), a.end());
    vector<vector<int>> ans;
    int n = (int)a.size();
    for (int i = 0; i + 2 < n; ++i) {
        if (i && a[i] == a[i-1]) continue;
        if (a[i] > 0) break;
        int l = i + 1, r = n - 1;
        while (l < r) {
            long long s = 1LL * a[i] + a[l] + a[r];
            if (s < 0) ++l;
            else if (s > 0) --r;
            else {
                ans.push_back({a[i], a[l], a[r]});
                int x = a[l], y = a[r];
                while (l < r && a[l] == x) ++l;
                while (l < r && a[r] == y) --r;
            }
        }
    }
    return ans;
}
