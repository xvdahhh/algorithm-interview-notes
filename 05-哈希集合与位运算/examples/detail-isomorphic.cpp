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

bool isIsomorphic(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    array<int, 256> forward, backward;
    forward.fill(-1); backward.fill(-1);
    for (size_t i = 0; i < s.size(); ++i) {
        unsigned char a = static_cast<unsigned char>(s[i]);
        unsigned char b = static_cast<unsigned char>(t[i]);
        if (forward[a] == -1 && backward[b] == -1) {
            forward[a] = b; backward[b] = a;
        } else if (forward[a] != b || backward[b] != a) {
            return false;
        }
    }
    return true;
}
