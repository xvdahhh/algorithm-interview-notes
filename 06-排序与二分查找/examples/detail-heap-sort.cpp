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

void siftDown(vector<int>& a, int root, int size) {
    while (root < size / 2) {
        int child = root * 2 + 1;
        if (child + 1 < size && a[child] < a[child + 1]) ++child;
        if (a[root] >= a[child]) break;
        swap(a[root], a[child]);
        root = child;
    }
}
void heapSort(vector<int>& a) {
    int n = (int)a.size();
    for (int root = n / 2 - 1; root >= 0; --root) siftDown(a, root, n);
    for (int end = n - 1; end > 0; --end) {
        swap(a[0], a[end]);
        siftDown(a, 0, end);
    }
}
