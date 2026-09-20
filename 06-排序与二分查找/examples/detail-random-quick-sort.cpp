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

void randomQuickRange(vector<int>& a, int l, int r, mt19937& rng) {
    while (l < r) {
        uniform_int_distribution<int> pick(l, r);
        int pivot = a[pick(rng)];
        int lt = l, i = l, gt = r;
        while (i <= gt) {
            if (a[i] < pivot) swap(a[lt++], a[i++]);
            else if (a[i] > pivot) swap(a[i], a[gt--]);
            else ++i;
        }
        if (lt - l < r - gt) {
            randomQuickRange(a, l, lt - 1, rng);
            l = gt + 1;
        } else {
            randomQuickRange(a, gt + 1, r, rng);
            r = lt - 1;
        }
    }
}
void randomizedQuickSort(vector<int>& a, uint32_t seed) {
    mt19937 rng(seed);
    if (!a.empty()) randomQuickRange(a, 0, (int)a.size() - 1, rng);
}
