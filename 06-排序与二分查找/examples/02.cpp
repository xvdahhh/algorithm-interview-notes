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

void quickSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int pivot = a[l + (r-l)/2];
    int lt=l, i=l, gt=r;
    while (i <= gt) {
        if (a[i] < pivot) swap(a[lt++], a[i++]);
        else if (a[i] > pivot) swap(a[i], a[gt--]);
        else ++i;
    }
    quickSort(a, l, lt-1);
    quickSort(a, gt+1, r);
}
void sortArray(vector<int>& a) {
    if (!a.empty()) quickSort(a, 0, (int)a.size()-1);
}
