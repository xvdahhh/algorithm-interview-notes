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

void siftDown(vector<int>& a, int i, int n) {
    while (2*i+1 < n) {
        int child=2*i+1;
        if (child+1<n && a[child+1]>a[child]) ++child;
        if (a[i]>=a[child]) break;
        swap(a[i],a[child]);
        i=child;
    }
}
void buildMaxHeap(vector<int>& a) {
    int n=(int)a.size();
    for (int i=n/2-1; i>=0; --i) siftDown(a,i,n);
}
