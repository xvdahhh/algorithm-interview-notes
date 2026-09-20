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

int kthSmallest(vector<int>& a, int k, uint32_t seed) {
    int n = (int)a.size();
    if (k < 1 || k > n) throw out_of_range("k outside [1,n]");
    int target = k - 1, l = 0, r = n - 1;
    mt19937 rng(seed);
    while (l <= r) {
        uniform_int_distribution<int> pick(l, r);
        int pivot = a[pick(rng)];
        int lt = l, i = l, gt = r;
        while (i <= gt) {
            if (a[i] < pivot) swap(a[lt++], a[i++]);
            else if (a[i] > pivot) swap(a[i], a[gt--]);
            else ++i;
        }
        if (target < lt) r = lt - 1;
        else if (target > gt) l = gt + 1;
        else return pivot;
    }
    throw logic_error("unreachable for valid input");
}
