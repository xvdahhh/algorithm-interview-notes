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

vector<int> twoSum(const vector<int>& a, long long target) {
    unordered_map<long long, int> pos;
    for (int i = 0; i < (int)a.size(); ++i) {
        auto it = pos.find(target - a[i]);
        if (it != pos.end()) return {it->second, i};
        pos[a[i]] = i;
    }
    return {};
}
