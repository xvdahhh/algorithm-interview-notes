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

struct Record {
    int key;
    int id; // original identity, not part of the sorting key
};
void stableMergeRange(vector<Record>& a, vector<Record>& tmp, int l, int r) {
    if (r - l <= 1) return;
    int m = l + (r - l) / 2;
    stableMergeRange(a, tmp, l, m);
    stableMergeRange(a, tmp, m, r);
    int i = l, j = m, out = l;
    while (i < m && j < r)
        tmp[out++] = a[i].key <= a[j].key ? a[i++] : a[j++];
    while (i < m) tmp[out++] = a[i++];
    while (j < r) tmp[out++] = a[j++];
    for (int k = l; k < r; ++k) a[k] = tmp[k];
}
void stableMergeSort(vector<Record>& a) {
    vector<Record> tmp(a.size());
    stableMergeRange(a, tmp, 0, (int)a.size());
}
