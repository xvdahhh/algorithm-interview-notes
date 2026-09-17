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

void mergeSortRange(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return;
    int m = l + (r-l)/2;
    mergeSortRange(a, tmp, l, m);
    mergeSortRange(a, tmp, m, r);
    int i=l, j=m, k=l;
    while (i<m && j<r)
        tmp[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i<m) tmp[k++] = a[i++];
    while (j<r) tmp[k++] = a[j++];
    for (int p=l; p<r; ++p) a[p]=tmp[p];
}
void mergeSort(vector<int>& a) {
    vector<int> tmp(a.size());
    mergeSortRange(a, tmp, 0, (int)a.size());
}
