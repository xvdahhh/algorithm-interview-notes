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

double medianOfSorted(const vector<int>& a, const vector<int>& b) {
    if (a.size() > b.size()) return medianOfSorted(b, a);
    int m = (int)a.size(), n = (int)b.size();
    if (m == 0 && n == 0) throw invalid_argument("both arrays empty");
    int half = (int)(((long long)m + n + 1) / 2);
    int l = 0, r = m;
    while (l <= r) {
        int i = l + (r - l) / 2, j = half - i;
        long long al = i == 0 ? LLONG_MIN : a[i - 1];
        long long ar = i == m ? LLONG_MAX : a[i];
        long long bl = j == 0 ? LLONG_MIN : b[j - 1];
        long long br = j == n ? LLONG_MAX : b[j];
        if (al <= br && bl <= ar) {
            if (((long long)m + n) % 2 != 0) return (double)max(al, bl);
            return (max(al, bl) + min(ar, br)) / 2.0;
        }
        if (al > br) r = i - 1;
        else l = i + 1;
    }
    throw invalid_argument("sorted input required");
}
