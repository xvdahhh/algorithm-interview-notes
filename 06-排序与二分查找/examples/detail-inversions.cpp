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

long long inversionRange(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int m = l + (r - l) / 2;
    long long answer = inversionRange(a, tmp, l, m);
    answer += inversionRange(a, tmp, m, r);
    int i = l, j = m, out = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) tmp[out++] = a[i++];
        else { answer += m - i; tmp[out++] = a[j++]; }
    }
    while (i < m) tmp[out++] = a[i++];
    while (j < r) tmp[out++] = a[j++];
    for (int k = l; k < r; ++k) a[k] = tmp[k];
    return answer;
}
long long countInversions(vector<int>& a) {
    vector<int> tmp(a.size());
    return inversionRange(a, tmp, 0, (int)a.size());
}
