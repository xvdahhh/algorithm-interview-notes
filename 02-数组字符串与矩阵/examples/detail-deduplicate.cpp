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

int removeDuplicatesSorted(vector<int>& a) {
    int write = 0;
    for (int read = 0; read < (int)a.size(); ++read) {
        if (write == 0 || a[read] != a[write - 1]) {
            a[write] = a[read];
            ++write;
        }
    }
    return write; // 仅 [0, write) 是结果，vector.size() 未改变
}
