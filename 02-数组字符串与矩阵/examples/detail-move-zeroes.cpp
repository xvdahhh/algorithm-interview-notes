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

void moveZeroes(vector<int>& a) {
    int write = 0;
    for (int read = 0; read < (int)a.size(); ++read) {
        if (a[read] != 0) a[write++] = a[read];
    }
    for (int i = write; i < (int)a.size(); ++i) a[i] = 0;
}
